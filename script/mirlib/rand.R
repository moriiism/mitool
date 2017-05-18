###
### rand.R
###

###
### Get Random Index
###
### [in]  int     num
### [out] vector  vec.ord
##        vector of random index
##

GetRandIndex <- function(num){
    ran.vec = runif(num)
    vec.ord = order(ran.vec)
    return(vec.ord)
}


GetNfoldRandIndex <- function(){



    
}
