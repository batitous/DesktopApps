/*

This file is part of lpc21isp.

    lpc21isp is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    lpc21isp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    and GNU General Public License along with lpc21isp.
    If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef LPC2ISP_LIB_H
#define LPC2ISP_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

// define LPC2ISP_EXPORTS for build the Dll
#ifdef _WIN32
#ifdef LPC2ISP_EXPORTS
#	define _DLL_SYMBOL __declspec(dllexport)
#else
#	define _DLL_SYMBOL __declspec(dllimport)
#endif
#else
#       define _DLL_SYMBOL extern
#endif

/** @brief Lpc2isp enumeration error */
typedef enum _lpc2isp_error_
{
	LPC2ISP_OK					= 0,	/**< No error */
	LPC2ISP_ERR_OPEN_HEX		= 1,	/**< Error to open hex file */
	LPC2ISP_ERR_LSEEK			= 2,	/**< Failed to seek hex file */
	LPC2ISP_ERR_BAD_FILE		= 3,	/**< Bad file: bad format or wrong data */
	LPC2ISP_ERR_OUT_OF_RANGE	= 4,	/**< Out of range... */
	LPC2ISP_ERR_OPEN_COM		= 5,	/**< Failed to open port com */
	LPC2ISP_ERR_SET_BAUD		= 6,	/**< Failed to set baudrate */
	LPC2ISP_ERR_DOWNLOAD		= 7,	/**< Error during upload process */
	LPC2ISP_ERR_NO_ANSWER		= 8		/**< No answer during upload protocol */

} lpc2ispError;

/** @brief Upload a hex file into a LPC21xx.
 *
 * @param serial		Serial port com.
 * @param hexFile		Path to the hex file.
 * @return 0 if no error, else error code.
 */
_DLL_SYMBOL lpc2ispError uploadToLpc21(char *serial, char *hexFile);

/** @brief Get upload progression.
 */
_DLL_SYMBOL unsigned int getUploadStatus(void);

#ifdef __cplusplus
}
#endif

#endif
