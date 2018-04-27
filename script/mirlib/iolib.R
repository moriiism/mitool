###
### iolib.R
###

printf <- function(s, ...) {
    cat(sprintf(s, ...))
}

fopen <- function(outfile) {
    cat("", file=outfile, append = FALSE)
}

fprintf <- function(outfile, s, ...) {
    cat(sprintf(s, ...), file=outfile, append = TRUE)
}
