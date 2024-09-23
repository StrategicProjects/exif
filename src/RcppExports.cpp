// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// read_exif_df
Rcpp::DataFrame read_exif_df(std::vector<std::string> image_paths);
RcppExport SEXP _exif_read_exif_df(SEXP image_pathsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<std::string> >::type image_paths(image_pathsSEXP);
    rcpp_result_gen = Rcpp::wrap(read_exif_df(image_paths));
    return rcpp_result_gen;
END_RCPP
}
// read_exif_list
Rcpp::List read_exif_list(std::vector<std::string> image_paths);
RcppExport SEXP _exif_read_exif_list(SEXP image_pathsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<std::string> >::type image_paths(image_pathsSEXP);
    rcpp_result_gen = Rcpp::wrap(read_exif_list(image_paths));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_exif_read_exif_df", (DL_FUNC) &_exif_read_exif_df, 1},
    {"_exif_read_exif_list", (DL_FUNC) &_exif_read_exif_list, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_exif(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
