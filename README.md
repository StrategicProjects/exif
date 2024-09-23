## Extract EXIF Metadata from JPEG Images

This package allows for the extraction of EXIF metadata from JPEG images using the easyexif library via Rcpp. The main function, read_exif, enables users to analyze one or multiple images and obtain the EXIF metadata in list or dataframe format. An advantage of this package is that it does not require any other tools to be installed on the system.

### Features

*	**Efficient EXIF Extraction:** Extract EXIF metadata from JPEG images efficiently using C++ and Rcpp.
*	**Multiple Image Support:** Analyze one or multiple images at once.
*	**Flexible Output Formats:** Returns data in either a list or a dataframe format.
*	**No External Dependencies:** No external tools required other than Rcpp and the included easyexif library.