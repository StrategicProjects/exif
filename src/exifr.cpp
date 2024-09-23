#include <Rcpp.h>
#include "exif.h"
#include <fstream>

/**
 * @title Extrair metadados EXIF de uma ou mais imagens
 * @description Esta função lê os metadados EXIF de uma ou mais imagens JPEG
 * e retorna os valores EXIF encontrados em uma lista. Utiliza a biblioteca
 * `easyexif` para realizar a extração dos dados.
 *
 * @param image_paths Vetor de strings contendo os caminhos para as imagens JPEG
 * que serão analisadas. Cada caminho deve corresponder a uma imagem válida.
 *
 * @return Uma lista onde cada elemento corresponde a uma imagem. Cada elemento
 * da lista contém outra lista com as informações EXIF da imagem.
 * 
 * @examples
 * \dontrun{
 *   # Suponha que você tenha dois arquivos de imagem JPEG
 *   image_paths <- c("imagem1.jpg", "imagem2.jpg")
 *   exif_data <- read_exif(image_paths)
 *   
 *   # Acessar os dados EXIF da primeira imagem
 *   print(exif_data$`imagem1.jpg`)
 * }
 *
 * @export
 */
// [[Rcpp::export(".read_exif_df")]]
Rcpp::DataFrame read_exif_df(std::vector<std::string> image_paths) {
  // Vetores para armazenar os resultados
  std::vector<std::string> img_paths;
  std::vector<std::string> exif_params;
  std::vector<std::string> exif_values;
  
  for (const auto& path : image_paths) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
      Rcpp::Rcerr << "Error: Can't open file: " << path << std::endl;
      continue;
    }
    
    // Ler o arquivo de imagem em um buffer
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::vector<unsigned char> buf(size);
    file.read(reinterpret_cast<char*>(&buf[0]), size);
    file.close();
    
    easyexif::EXIFInfo result;
    int code = result.parseFrom(buf.data(), buf.size());
    if (code) {
      Rcpp::Rcerr << "Error parsing EXIF for file: " << path << std::endl;
      continue;
    }
    
    // Adicionar informações EXIF ao vetor
    img_paths.push_back(path); exif_params.push_back("Camera Make"); exif_values.push_back(result.Make);
    img_paths.push_back(path); exif_params.push_back("Camera Model"); exif_values.push_back(result.Model);
    img_paths.push_back(path); exif_params.push_back("Software"); exif_values.push_back(result.Software);
    img_paths.push_back(path); exif_params.push_back("Bits Per Sample"); exif_values.push_back(std::to_string(result.BitsPerSample));
    img_paths.push_back(path); exif_params.push_back("Image Width"); exif_values.push_back(std::to_string(result.ImageWidth));
    img_paths.push_back(path); exif_params.push_back("Image Height"); exif_values.push_back(std::to_string(result.ImageHeight));
    img_paths.push_back(path); exif_params.push_back("Image Description"); exif_values.push_back(result.ImageDescription);
    img_paths.push_back(path); exif_params.push_back("Orientation"); exif_values.push_back(std::to_string(result.Orientation));
    img_paths.push_back(path); exif_params.push_back("Copyright"); exif_values.push_back(result.Copyright);
    img_paths.push_back(path); exif_params.push_back("DateTime"); exif_values.push_back(result.DateTime);
    img_paths.push_back(path); exif_params.push_back("Original DateTime"); exif_values.push_back(result.DateTimeOriginal);
    img_paths.push_back(path); exif_params.push_back("Digitized DateTime"); exif_values.push_back(result.DateTimeDigitized);
    img_paths.push_back(path); exif_params.push_back("Subsecond Time"); exif_values.push_back(result.SubSecTimeOriginal);
    img_paths.push_back(path); exif_params.push_back("Exposure Time"); exif_values.push_back(std::to_string(result.ExposureTime));
    img_paths.push_back(path); exif_params.push_back("F-Stop"); exif_values.push_back(std::to_string(result.FNumber));
    img_paths.push_back(path); exif_params.push_back("Exposure Program"); exif_values.push_back(std::to_string(result.ExposureProgram));
    img_paths.push_back(path); exif_params.push_back("ISO Speed"); exif_values.push_back(std::to_string(result.ISOSpeedRatings));
    img_paths.push_back(path); exif_params.push_back("Subject Distance"); exif_values.push_back(std::to_string(result.SubjectDistance));
    img_paths.push_back(path); exif_params.push_back("Exposure Bias"); exif_values.push_back(std::to_string(result.ExposureBiasValue));
    img_paths.push_back(path); exif_params.push_back("Flash Used"); exif_values.push_back(std::to_string(result.Flash));
    img_paths.push_back(path); exif_params.push_back("Flash Returned Light"); exif_values.push_back(std::to_string(result.FlashReturnedLight));
    img_paths.push_back(path); exif_params.push_back("Flash Mode"); exif_values.push_back(std::to_string(result.FlashMode));
    img_paths.push_back(path); exif_params.push_back("Metering Mode"); exif_values.push_back(std::to_string(result.MeteringMode));
    img_paths.push_back(path); exif_params.push_back("Focal Length"); exif_values.push_back(std::to_string(result.FocalLength));
    img_paths.push_back(path); exif_params.push_back("Focal Length in 35mm"); exif_values.push_back(std::to_string(result.FocalLengthIn35mm));
    img_paths.push_back(path); exif_params.push_back("GPS Latitude"); exif_values.push_back(std::to_string(result.GeoLocation.Latitude));
    img_paths.push_back(path); exif_params.push_back("GPS Longitude"); exif_values.push_back(std::to_string(result.GeoLocation.Longitude));
    img_paths.push_back(path); exif_params.push_back("GPS Altitude"); exif_values.push_back(std::to_string(result.GeoLocation.Altitude));
    img_paths.push_back(path); exif_params.push_back("GPS Precision (DOP)"); exif_values.push_back(std::to_string(result.GeoLocation.DOP));
    img_paths.push_back(path); exif_params.push_back("Lens Min Focal Length"); exif_values.push_back(std::to_string(result.LensInfo.FocalLengthMin));
    img_paths.push_back(path); exif_params.push_back("Lens Max Focal Length"); exif_values.push_back(std::to_string(result.LensInfo.FocalLengthMax));
    img_paths.push_back(path); exif_params.push_back("Lens F-Stop Min"); exif_values.push_back(std::to_string(result.LensInfo.FStopMin));
    img_paths.push_back(path); exif_params.push_back("Lens F-Stop Max"); exif_values.push_back(std::to_string(result.LensInfo.FStopMax));
    img_paths.push_back(path); exif_params.push_back("Lens Make"); exif_values.push_back(result.LensInfo.Make);
    img_paths.push_back(path); exif_params.push_back("Lens Model"); exif_values.push_back(result.LensInfo.Model);
    img_paths.push_back(path); exif_params.push_back("Focal Plane X Resolution"); exif_values.push_back(std::to_string(result.LensInfo.FocalPlaneXResolution));
    img_paths.push_back(path); exif_params.push_back("Focal Plane Y Resolution"); exif_values.push_back(std::to_string(result.LensInfo.FocalPlaneYResolution));
  }
  
  // Retornar um DataFrame
  return Rcpp::DataFrame::create(
    Rcpp::Named("image_path") = img_paths,
    Rcpp::Named("exif_param") = exif_params,
    Rcpp::Named("exif_value") = exif_values
  );
}

/**
 * @title Extrair metadados EXIF de uma ou mais imagens
 * @description Esta função lê os metadados EXIF de uma ou mais imagens JPEG
 * e retorna os valores EXIF encontrados em uma lista. Utiliza a biblioteca
 * `easyexif` para realizar a extração dos dados.
 *
 * @param image_paths Vetor de strings contendo os caminhos para as imagens JPEG
 * que serão analisadas. Cada caminho deve corresponder a uma imagem válida.
 *
 * @return Uma lista onde cada elemento corresponde a uma imagem. Cada elemento
 * da lista contém outra lista com as informações EXIF da imagem.
 * 
 * @examples
 * \dontrun{
 *   # Suponha que você tenha dois arquivos de imagem JPEG
 *   image_paths <- c("imagem1.jpg", "imagem2.jpg")
 *   exif_data <- read_exif(image_paths)
 *   
 *   # Acessar os dados EXIF da primeira imagem
 *   print(exif_data$`imagem1.jpg`)
 * }
 *
 * @export
 */
// [[Rcpp::export(".read_exif_list")]]
Rcpp::List read_exif_list(std::vector<std::string> image_paths) {
  Rcpp::List results;
  
  for (const auto& path : image_paths) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
      Rcpp::Rcerr << "Error: Can't open file: " << path << std::endl;
      continue;
    }
    
    // Ler o arquivo de imagem em um buffer
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::vector<unsigned char> buf(size);
    file.read(reinterpret_cast<char*>(&buf[0]), size);
    file.close();
    
    easyexif::EXIFInfo result;
    int code = result.parseFrom(buf.data(), buf.size());
    if (code) {
      Rcpp::Rcerr << "Error parsing EXIF for file: " << path << std::endl;
      continue;
    }
    
    // Criar uma lista para armazenar os valores EXIF
    Rcpp::List exif_info = Rcpp::List::create(
      Rcpp::Named("Camera Make") = result.Make,
      Rcpp::Named("Camera Model") = result.Model,
      Rcpp::Named("Software") = result.Software,
      Rcpp::Named("Bits Per Sample") = result.BitsPerSample,
      Rcpp::Named("Image Width") = result.ImageWidth,
      Rcpp::Named("Image Height") = result.ImageHeight,
      Rcpp::Named("Image Description") = result.ImageDescription,
      Rcpp::Named("Orientation") = result.Orientation,
      Rcpp::Named("Copyright") = result.Copyright,
      Rcpp::Named("DateTime") = result.DateTime,
      Rcpp::Named("Original DateTime") = result.DateTimeOriginal,
      Rcpp::Named("Digitized DateTime") = result.DateTimeDigitized,
      Rcpp::Named("Subsecond Time") = result.SubSecTimeOriginal,
      Rcpp::Named("Exposure Time") = result.ExposureTime,
      Rcpp::Named("F-Stop") = result.FNumber,
      Rcpp::Named("Exposure Program") = result.ExposureProgram,
      Rcpp::Named("ISO Speed") = result.ISOSpeedRatings,
      Rcpp::Named("Subject Distance") = result.SubjectDistance,
      Rcpp::Named("Exposure Bias") = result.ExposureBiasValue,
      Rcpp::Named("Flash Used") = result.Flash,
      Rcpp::Named("Flash Returned Light") = result.FlashReturnedLight,
      Rcpp::Named("Flash Mode") = result.FlashMode,
      Rcpp::Named("Metering Mode") = result.MeteringMode,
      Rcpp::Named("Focal Length") = result.FocalLength,
      Rcpp::Named("Focal Length in 35mm") = result.FocalLengthIn35mm,
      Rcpp::Named("GPS Latitude") = result.GeoLocation.Latitude,
      Rcpp::Named("GPS Longitude") = result.GeoLocation.Longitude,
      Rcpp::Named("GPS Altitude") = result.GeoLocation.Altitude,
      Rcpp::Named("GPS Precision (DOP)") = result.GeoLocation.DOP,
      Rcpp::Named("Lens Min Focal Length") = result.LensInfo.FocalLengthMin,
      Rcpp::Named("Lens Max Focal Length") = result.LensInfo.FocalLengthMax,
      Rcpp::Named("Lens F-Stop Min") = result.LensInfo.FStopMin,
      Rcpp::Named("Lens F-Stop Max") = result.LensInfo.FStopMax,
      Rcpp::Named("Lens Make") = result.LensInfo.Make,
      Rcpp::Named("Lens Model") = result.LensInfo.Model,
      Rcpp::Named("Focal Plane X Resolution") = result.LensInfo.FocalPlaneXResolution,
      Rcpp::Named("Focal Plane Y Resolution") = result.LensInfo.FocalPlaneYResolution
    );
    
    results[path] = exif_info;
  }
  
  return results;
}