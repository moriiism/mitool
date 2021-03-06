###
### binning.R
###

###
### edge
###

GetPoint <- function(npoint, lo, up, scale){
    vec = vector()
    if("lin" == scale){
        vec = GetPointLin(npoint, lo, up)
    }
    else if ("log" == scale){
        vec = GetPointLog(npoint, lo, up)
    }
    else {
        stop()
    }
    return(vec)
}

GetPointLin <- function(npoint, lo, up){
    delta = 0.0
    if(npoint > 1){
        delta = ( up - lo ) / (npoint - 1)
    }
    else {
        delta = 0.0
    }
    vec = vector()
    for(i.val in 1:npoint){
        vec[i.val] = lo + (i.val - 1) * delta
    }
    return(vec)
}

GetPointLog <- function(npoint, lo, up){
    delta = 0.0
    if(npoint > 1){
        delta = ( log10(up) - log10(lo) ) / (npoint - 1)
    }
    else {
        delta = 0.0
    }
    vec = vector()
    for(i.val in 1:npoint){
        vec[i.val] = 10.0^( log10(lo) + (i.val - 1) * delta )
    }
    return(vec)
}


###
### center
###
