
#include <cereal/archives/json.hpp>

#include "openMVG/features/image_describer_akaze_io.hpp"

#include "openMVG/features/sift/SIFT_Anatomy_Image_Describer_io.hpp"
#include "openMVG/image/image_io.hpp"
#include "openMVG/features/regions_factory_io.hpp"
#include "openMVG/sfm/sfm_data.hpp"
#include "openMVG/sfm/sfm_data_io.hpp"
#include "openMVG/system/timer.hpp"

#include "third_party/cmdLine/cmdLine.h"
#include "third_party/progress/progress_display.hpp"
#include "third_party/stlplus3/filesystemSimplified/file_system.hpp"

#include "nonFree/sift/SIFT_describer_io.hpp"

#include <cereal/details/helpers.hpp>

#include <atomic>
#include <cstdlib>
#include <fstream>
#include <string>

#ifdef OPENMVG_USE_OPENMP
#include <omp.h>
#endif

using namespace openMVG;
using namespace openMVG::image;
using namespace openMVG::features;
using namespace openMVG::sfm;
using namespace std;

features::EDESCRIBER_PRESET stringToEnum(const std::string & sPreset)
{
  features::EDESCRIBER_PRESET preset;
  if (sPreset == "NORMAL")
    preset = features::NORMAL_PRESET;
  else
  if (sPreset == "HIGH")
    preset = features::HIGH_PRESET;
  else
  if (sPreset == "ULTRA")
    preset = features::ULTRA_PRESET;
  else
    preset = features::EDESCRIBER_PRESET(-1);
  return preset;
}

int main(int argc, char **argv)
{
  CmdLine cmd;

  std::string sSfM_Data_Filename;
  std::string sOutDir = "";
  bool bUpRight = false;
  std::string sImage_Describer_Method = "SIFT";
  bool bForce = false;
  std::string sFeaturePreset = "";
#ifdef OPENMVG_USE_OPENMP
  int iNumThreads = 0;
#endif


  cmd.add( make_option('i', sSfM_Data_Filename, "input_file") );
  cmd.add( make_option('o', sOutDir, "outdir") );


  cmd.add( make_option('m', sImage_Describer_Method, "describerMethod") );
  cmd.add( make_option('u', bUpRight, "upright") );
  cmd.add( make_option('f', bForce, "force") );
  cmd.add( make_option('p', sFeaturePreset, "describerPreset") );

#ifdef OPENMVG_USE_OPENMP
  cmd.add( make_option('n', iNumThreads, "numThreads") );
#endif

  try {
      if (argc == 1) throw std::string("Invalid command line parameter.");
      cmd.process(argc, argv);
  } catch (const std::string& s) {
      std::cerr << "Usage: " << argv[0] << '\n'
      << "[-i|--input_file] a SfM_Data file \n"
      << "[-o|--outdir path] \n"
      << "\n[Optional]\n"
      << "[-f|--force] Force to recompute data\n"
      << "[-m|--describerMethod]\n"
      << "  (method to use to describe an image):\n"
      << "   SIFT (default),\n"
      << "   SIFT_ANATOMY,\n"
      << "   AKAZE_FLOAT: AKAZE with floating point descriptors,\n"
      << "   AKAZE_MLDB:  AKAZE with binary descriptors\n"
      << "[-u|--upright] Use Upright feature 0 or 1\n"
      << "[-p|--describerPreset]\n"
      << "  (used to control the Image_describer configuration):\n"
      << "   NORMAL (default),\n"
      << "   HIGH,\n"
      << "   ULTRA: !!Can take long time!!\n"
#ifdef OPENMVG_USE_OPENMP
      << "[-n|--numThreads] number of parallel computations\n"
#endif
      << std::endl;

      std::cerr << s << std::endl;
      return EXIT_FAILURE;
  }

  std::cout << " You called : " <<std::endl
            << argv[0] << std::endl
            << "--input_file " << sSfM_Data_Filename << std::endl
            << "--outdir " << sOutDir << std::endl
            << "--describerMethod " << sImage_Describer_Method << std::endl
            << "--upright " << bUpRight << std::endl
            << "--describerPreset " << (sFeaturePreset.empty() ? "NORMAL" : sFeaturePreset) << std::endl
            << "--force " << bForce << std::endl
#ifdef OPENMVG_USE_OPENMP
            << "--numThreads " << iNumThreads << std::endl
#endif
            << std::endl;


  if (sOutDir.empty())  {
    std::cerr << "\nIt is an invalid output directory" << std::endl;
    return EXIT_FAILURE;
  }

  // Crear directorio
  if (!stlplus::folder_exists(sOutDir))
  {
    if (!stlplus::folder_create(sOutDir))
    {
      std::cerr << "Cannot create output directory" << std::endl;
      return EXIT_FAILURE;
    }
  }

  //---------------------------------------
  // a. carga la entrada
  //---------------------------------------
  SfM_Data sfm_data;
  if (!Load(sfm_data, sSfM_Data_Filename, ESfM_Data(VIEWS|INTRINSICS))) {
    std::cerr << std::endl
      << "The input file \""<< sSfM_Data_Filename << "\" cannot be read" << std::endl;
    return EXIT_FAILURE;
  }

  // b. incializa el descriptor
  // - devuelve el que se uso en caso de que ya se compute las caracteristicas

  using namespace openMVG::features;
  std::unique_ptr<Image_describer> image_describer;

  const std::string sImage_describer = stlplus::create_filespec(sOutDir, "image_describer", "json");
  if (!bForce && stlplus::is_file(sImage_describer))
  {
    
    std::ifstream stream(sImage_describer.c_str());
    if (!stream.is_open())
      return EXIT_FAILURE;

    try
    {
      cereal::JSONInputArchive archive(stream);
      archive(cereal::make_nvp("image_describer", image_describer));
    }
    catch (const cereal::Exception & e)
    {
      std::cerr << e.what() << std::endl
        << "Cannot dynamically allocate the Image_describer interface." << std::endl;
      return EXIT_FAILURE;
    }
  }
  else
  {
    if (sImage_Describer_Method == "SIFT")
    {
      image_describer.reset(new SIFT_Image_describer
        (SIFT_Image_describer::Params(), !bUpRight));
    }
    else
    if (sImage_Describer_Method == "SIFT_ANATOMY")
    {
      image_describer.reset(
        new SIFT_Anatomy_Image_describer(SIFT_Anatomy_Image_describer::Params()));
    }
    else
    if (sImage_Describer_Method == "AKAZE_FLOAT")
    {
      image_describer = AKAZE_Image_describer::create
        (AKAZE_Image_describer::Params(AKAZE::Params(), AKAZE_MSURF), !bUpRight);
    }
    else
    if (sImage_Describer_Method == "AKAZE_MLDB")
    {
      image_describer = AKAZE_Image_describer::create
        (AKAZE_Image_describer::Params(AKAZE::Params(), AKAZE_MLDB), !bUpRight);
    }
    if (!image_describer)
    {
      std::cerr << "Cannot create the designed Image_describer:"
        << sImage_Describer_Method << "." << std::endl;
      return EXIT_FAILURE;
    }
    else
    {
      if (!sFeaturePreset.empty())
      if (!image_describer->Set_configuration_preset(stringToEnum(sFeaturePreset)))
      {
        std::cerr << "Preset configuration failed." << std::endl;
        return EXIT_FAILURE;
      }
    }

    {
      std::ofstream stream(sImage_describer.c_str());
      if (!stream.is_open())
        return EXIT_FAILURE;

      cereal::JSONOutputArchive archive(stream);
      archive(cereal::make_nvp("image_describer", image_describer));
      auto regionsType = image_describer->Allocate();
      archive(cereal::make_nvp("regions_type", regionsType));
    }
  }

  // routinas de extracción de caracteristicas
  // para cada vusta de SfM_Data container:
  // - si el archivo de regiones existe continua
  // - si no hay archivo, calcula las caracteristicas
  {
    system::Timer timer;
    Image<unsigned char> imageGray;

    C_Progress_display my_progress_bar(sfm_data.GetViews().size(),
      std::cout, "\n- EXTRACCION DE CARACTERISTICAS -\n" );

    
    std::atomic<bool> preemptive_exit(false);
#ifdef OPENMVG_USE_OPENMP
    const unsigned int nb_max_thread = omp_get_max_threads();

    if (iNumThreads > 0) {
        omp_set_num_threads(iNumThreads);
    } else {
        omp_set_num_threads(nb_max_thread);
    }

    #pragma omp parallel for schedule(dynamic) if (iNumThreads > 0) private(imageGray)
#endif
    for (int i = 0; i < static_cast<int>(sfm_data.views.size()); ++i)
    {
      Views::const_iterator iterViews = sfm_data.views.begin();
      std::advance(iterViews, i);
      const View * view = iterViews->second.get();
      const std::string
        sView_filename = stlplus::create_filespec(sfm_data.s_root_path, view->s_Img_path),
        sFeat = stlplus::create_filespec(sOutDir, stlplus::basename_part(sView_filename), "feat"),
        sDesc = stlplus::create_filespec(sOutDir, stlplus::basename_part(sView_filename), "desc");

      
      if (!preemptive_exit && (bForce || !stlplus::file_exists(sFeat) || !stlplus::file_exists(sDesc)))
      {
        if (!ReadImage(sView_filename.c_str(), &imageGray))
          continue;

        
        Image<unsigned char> * mask = nullptr; // mascara nula por defecto

        const std::string
          mask_filename_local =
            stlplus::create_filespec(sfm_data.s_root_path,
              stlplus::basename_part(sView_filename) + "_mask", "png"),
          mask__filename_global =
            stlplus::create_filespec(sfm_data.s_root_path, "mask", "png");

        Image<unsigned char> imageMask;
        
        if (stlplus::file_exists(mask_filename_local))
        {
          if (!ReadImage(mask_filename_local.c_str(), &imageMask))
          {
            std::cerr << "Invalid mask: " << mask_filename_local << std::endl
                      << "Stopping feature extraction." << std::endl;
            preemptive_exit = true;
            continue;
          }
          
          if (imageMask.Width() == imageGray.Width() && imageMask.Height() == imageGray.Height())
            mask = &imageMask;
        }
        else
        {
          
          if (stlplus::file_exists(mask__filename_global))
          {
            if (!ReadImage(mask__filename_global.c_str(), &imageMask))
            {
              std::cerr << "Invalid mask: " << mask__filename_global << std::endl
                        << "Stopping feature extraction." << std::endl;
              preemptive_exit = true;
              continue;
            }
            
            if (imageMask.Width() == imageGray.Width() && imageMask.Height() == imageGray.Height())
              mask = &imageMask;
          }
        }

        
        auto regions = image_describer->Describe(imageGray, mask);
        if (regions && !image_describer->Save(regions.get(), sFeat, sDesc)) {
          std::cerr << "Cannot save regions for images: " << sView_filename << std::endl
                    << "Stopping feature extraction." << std::endl;
          preemptive_exit = true;
          continue;
        }
      }
      ++my_progress_bar;
    }
    std::cout << "Tarea hecha en (s): " << timer.elapsed() << std::endl;
  }
  return EXIT_SUCCESS;
}
