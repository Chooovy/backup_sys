#ifndef _HEADER_H_
#define _HEADER_H_

#include <vector>
#include <string>
#include <cstring>

/* tar Header Block, from POSIX 1003.1-1990.  */

/* POSIX header.  */

// #define BLOCKSIZE 500

// name：文件名，最多100个字符，以null结尾字符串。
// mode：文件权限和类型，以八进制字符串表示，例如 "0755" 表示文件权限为755（rwxr-xr-x）。
// uid：所有者的用户ID，以八进制字符串表示。
// gid：所有者的组ID，以八进制字符串表示。
// size：文件大小，以八进制字符串表示。
// mtime：修改时间，以八进制字符串表示，表示自1970年1月1日以来的秒数。
// chksum：校验和，以八进制字符串表示。
// typeflag：文件类型，表示文件、目录等。常见的值包括 '0'（普通文件）、'5'（目录）等。
// linkname：链接的目标文件名，如果不是链接则为空。
// magic：文件头魔术字符串，通常为 "ustar"。
// version：ustar版本号，通常为 "00"。
// uname：所有者的用户名，以null结尾字符串。
// gname：所有者的组名，以null结尾字符串。
// devmajor：设备文件的主要设备号，以八进制字符串表示。
// devminor：设备文件的次要设备号，以八进制字符串表示。
// prefix：文件名的前缀，以null结尾字符串。


struct posix_header
{                              /* byte offset */
  char name[100];               /*   0 */
  char mode[8];                 /* 100 */
  char uid[8];                  /* 108 */
  char gid[8];                  /* 116 */
  char size[12];                /* 124 */
  char mtime[12];               /* 136 */
  char chksum[7];               /* 148 */
  char typeflag[2];             /* 156 */
  char linkname[100];           /* 157 */
  char magic[5];                /* 257 */
  char version[3];              /* 263 */
  char uname[32];               /* 265 */
  char gname[32];               /* 297 */
  char devmajor[8];             /* 329 */
  char devminor[8];             /* 337 */
  char prefix[155];             /* 345 */
  char padding[12];             /* 500 */
  posix_header() : name("\0"), mode("\0"), uid("\0"), gid("\0"), size("\0"), mtime("\0"), chksum("\0"), typeflag("\0"), linkname("\0"), magic("\0"), version("\0"), uname("\0"), gname("\0"), devmajor("\0"), devminor("\0"), prefix("\0"), padding("\0"){}
} ;

#define TMAGIC   "ustar"        /* ustar and a null */
#define TMAGLEN  6
#define TVERSION "00"           /* 00 and no null */
#define TVERSLEN 2

/* Values used in typeflag field.  */
#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* link */
#define SYMTYPE  '2'            /* reserved */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */

#define XHDTYPE  'x'            /* Extended header referring to the next file in the archive */
#define XGLTYPE  'g'            /* Global extended header */

/* Bits used in the mode field, values in octal.  */
#define TSUID    04000          /* set UID on execution */
#define TSGID    02000          /* set GID on execution */
#define TSVTX    01000          /* reserved */
                                /* file permissions */
#define TUREAD   00400          /* read by owner */
#define TUWRITE  00200          /* write by owner */
#define TUEXEC   00100          /* execute/search by owner */
#define TGREAD   00040          /* read by group */
#define TGWRITE  00020          /* write by group */
#define TGEXEC   00010          /* execute/search by group */
#define TOREAD   00004          /* read by other */
#define TOWRITE  00002          /* write by other */
#define TOEXEC   00001          /* execute/search by other */

#endif