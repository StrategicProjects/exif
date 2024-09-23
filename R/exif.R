#' @title Extract EXIF metadata with path expansion
#' @description This function is a wrapper that expands the provided image file paths (e.g.,
#' converts "~" to the user's home directory path) and calls the C++ function `read_exif_cpp`
#' to extract the EXIF metadata from JPEG images.
#'
#' @param image_paths A vector of strings containing the paths to the JPEG images to be analyzed.
#' The paths may contain the "~" symbol to represent the user's home directory.
#' @param list A logical value indicating whether you want the output as a list (`TRUE`) or
#' a dataframe (`FALSE`).
#'
#' @return If `list = TRUE`, returns a list where each element corresponds to an image. Each element
#' of the list contains another list with the EXIF information of the image. If `list = FALSE`,
#' returns a dataframe with three columns: the image path, the EXIF parameter name, and the
#' parameter value.
#'
#' @examples
#' \dontrun{
#'   # Suppose you have two JPEG image files with paths using "~"
#'   image_paths <- c("~/images/image1.jpg", "~/images/image2.jpg")
#'   # Get EXIF data as a list
#'   exif_data_list <- read_exif(image_paths, list = TRUE)
#'   # Get EXIF data as a dataframe
#'   exif_data_df <- read_exif(image_paths, list = FALSE)
#' }
#'
#' @export
read_exif <- function(image_paths, list = FALSE) {
  # Expandir os caminhos para garantir que estão completos
  expanded_paths <- path.expand(image_paths)
  
  # Chamar a função C++ passando os caminhos expandidos
  if(list)
    .read_exif_list(expanded_paths)
  else 
    .read_exif_df(expanded_paths)
}