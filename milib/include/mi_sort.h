#ifndef MORIIISM_MILIB_SORT_H_
#define MORIIISM_MILIB_SORT_H_

//
// made from TMath.h of ROOT tool developed at CERN.
//

namespace MiSort
{
    template<typename T>
    struct CompareDesc {
        CompareDesc(T d) : fData(d) {}
        template<typename Index>
        bool operator()(Index i1, Index i2) {
            return *(fData + i1) > *(fData + i2);
        }
        T fData;
    };
 
    template<typename T>
    struct CompareAsc {
        CompareAsc(T d) : fData(d) {}
        template<typename Index>
        bool operator()(Index i1, Index i2) {
            return *(fData + i1) < *(fData + i2);
        }
        T fData;
    };
 
    template <typename Element, typename Index>
    void Sort(Index n, const Element* a, Index* index, bool down)
    {
        // Sort the n elements of the  array a of generic templated type Element.
        // In output the array index of type Index contains the indices of the sorted array.
        // If down is false sort in increasing order (default is decreasing order).

        // NOTE that the array index must be created with a length >= n
        // before calling this function.
        // NOTE also that the size type for n must be the same type used for the index array
        // (templated type Index)

        // template< class RandomIt, class Compare >
        // void sort( RandomIt first, RandomIt last, Compare comp );
        for(Index i = 0; i < n; i++) { index[i] = i; }
        if ( down )
            std::sort(index, index + n, CompareDesc<const Element*>(a) );
        else
            std::sort(index, index + n, CompareAsc<const Element*>(a) );
    }

    
    // 0, ..., k,..., n
    template <typename Element, typename Index>
    void KthElement(Index k, Index n, const Element* a, Index* index, bool down)
    {
        for(Index i = 0; i < n; i++) { index[i] = i; }

        // template< class RandomIt, class Compare >
        // void nth_element( RandomIt first, RandomIt nth, RandomIt last, Compare comp );
        if ( down )
            std::nth_element(index, index + k, index + n, CompareDesc<const Element*>(a) );
        else
            std::nth_element(index, index + k, index + n, CompareAsc<const Element*>(a) );
    }
}

#endif // MORIIISM_MILIB_SORT_H_
