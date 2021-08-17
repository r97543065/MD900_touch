#ifndef __Panel_define_H
#define __Panel_define_H

#ifdef __cplusplus
 extern "C" {
#endif

//#define Panel_SF_TC240T
//#define Panel_VT035A
//#define Panel_VGA640x480
#define Panel_VGA800x600
//#define Panel_VGA1024x768
//#define Panel_VGA1280x800
//#define Panel_VGA1366x768

#if defined(Panel_SF_TC240T)
#include "Panel_SF_TC240T.h"
#elif defined (Panel_VT035A)
#include "Panel_VT035A.h"
#elif defined (Panel_VGA640x480)
#include "Panel_VGA640x480.h"
#elif defined (Panel_VGA800x600)
#include "Panel_VGA800x600.h"
#elif defined (Panel_VGA1024x768)
#include "Panel_VGA1024x768.h"
#elif defined (Panel_VGA1280x800)
#include "Panel_VGA1280x800.h"
#elif defined (Panel_VGA1366x768)
#include "Panel_VGA1366x768.h"
#else
 #error "You did not choose any type panel!"
#endif


#ifdef __cplusplus
}
#endif

#endif /*__Panel_define_H */

