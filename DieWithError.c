//
//  DieWithError.c
//  ECE3600
//
//  Created by Felix Xiao on 9/23/14.
//
//

#include <stdio.h>  /* for perror() */
#include <stdlib.h> /* for exit() */

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
