/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BUILD_VERSION_H
#define _BUILD_VERSION_H

/* WARNING
Don't modify the file structure!
*/

/* Exported constants --------------------------------------------------------*/
#define BUILD_VER_SCALER		(10000)

#define BUILD_VERSION_MAJOR     (1)
#define BUILD_VERSION_MINOR     (5)

#define BUILD_TIMESTAMP         ("2017-05-03 14:26")

#define BUILD_NUMBER			(BUILD_VERSION_MAJOR * BUILD_VER_SCALER + BUILD_VERSION_MINOR)

#endif //_BUILD_VERSION_H
