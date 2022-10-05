// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Alexis Torres
// at39625
// Slip days used: 0
// Spring 2022


#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "UTString.h"

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}

/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
    UTString *wordString = (struct UTString*)malloc(sizeof(struct UTString)); // allocates memory on the heap with the size of the UTstring
    wordString-> string = (char*)malloc(sizeof(char)*(strlen(src)+5)); // allocates to the size of the of char (4 bytes) times the length of of the string plus 5 for the buffer
    wordString-> capacity = strlen(src);
    wordString-> length = strlen(src);
    uint32_t len = strlen(src);//to keep track in the for loop
    uint32_t i;
    for(i =0; i<=len; i++){
        wordString->string[i] = src[i];
    }
    CHECK(wordString) = SIGNATURE; // add the beef at the end
    return wordString;
}

/*
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
    assert(isOurs(s));//checks if it is valid
   uint32_t utLen = strlen(s->string);
//    uint32_t  utLen =0;
//    while(s->string[utLen] =! '\0'){
//        utLen++;
//    }
       return utLen;
  }


/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    assert(isOurs(s));//checks if it valid
    uint32_t len = s->length;
    uint32_t cap = s->capacity;
    uint32_t i = 0;
       while (cap > len && suffix[i] != '\0') { //check if it is not a null and there is space
           s->string[len] = suffix[i];
           len++;
           i++;
       }
    s->length+=i;
    s->string[len]='\0';
    CHECK(s)=SIGNATURE;           // at the adds the ending beef
    return s;
   }


/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    assert(isOurs(dst));
    uint32_t i = 0;
    uint32_t dst_cap = dst->capacity;
    uint32_t src_cap = strlen(src);
        while ((i< dst_cap) && (i<src_cap)){//keeps looping until it reaches the null of src or it exceeds capcity
            dst->string[i] = *(src+ i);
            i++;
    }
    dst->string[i]='\0';        //puts the null at the end of the new string
    dst->length=i;
    CHECK(dst)=SIGNATURE;           // at the adds the ending beef

    return dst;

}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
    assert(isOurs(self));
    free(self->string);
    free(self);
}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    assert(isOurs(s));
    if(s->capacity < new_capacity){ // if the cap is less than the new_cap then change
        s->capacity = new_capacity;
        s->string = (char *) realloc(s->string, sizeof(char)*(new_capacity + 5));
        return s;
    }
    else {//but if it is equal or greater, then nothing is needed
        return s;
    }
}
