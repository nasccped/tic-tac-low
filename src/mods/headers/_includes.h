#ifndef __INCLUDES_H_
#define __INCLUDES_H_

/* ------------------------------------------------------------------
 *
 * _includes.h
 *
 *     this is a header include file. In a normal way, I'll need to
 *     o every import within a c file. Basically, i will copy and
 *     past a <stdio.h> a lot of times. But... I can also build a
 *     header file that store all the includes and include it after
 *     in each c file.
 *
 *     looks a good strategy :^D
 * --------------------------------------------------------------- */

// including stdio.h if isn't already included
#ifndef _STDIO_H_
  #include <stdio.h>
#endif

// including string.h if isn't already included
#ifndef _STRING_H_
  #include <string.h>
#endif

// including stdlib.h if isn't already included
#ifndef _STDLIB_H_
  #include <stdlib.h>
#endif



#endif
