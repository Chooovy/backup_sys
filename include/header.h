#ifndef _HEADER_H_
#define _HEADER_H_

#include <vector>
#include <string>
#include <cstring>

/* tar Header Block, from POSIX 1003.1-1990.  */

/* POSIX header.  */

// #define BLOCKSIZE 500

// name���ļ��������100���ַ�����null��β�ַ�����
// mode���ļ�Ȩ�޺����ͣ��԰˽����ַ�����ʾ������ "0755" ��ʾ�ļ�Ȩ��Ϊ755��rwxr-xr-x����
// uid�������ߵ��û�ID���԰˽����ַ�����ʾ��
// gid�������ߵ���ID���԰˽����ַ�����ʾ��
// size���ļ���С���԰˽����ַ�����ʾ��
// mtime���޸�ʱ�䣬�԰˽����ַ�����ʾ����ʾ��1970��1��1��������������
// chksum��У��ͣ��԰˽����ַ�����ʾ��
// typeflag���ļ����ͣ���ʾ�ļ���Ŀ¼�ȡ�������ֵ���� '0'����ͨ�ļ�����'5'��Ŀ¼���ȡ�
// linkname�����ӵ�Ŀ���ļ������������������Ϊ�ա�
// magic���ļ�ͷħ���ַ�����ͨ��Ϊ "ustar"��
// version��ustar�汾�ţ�ͨ��Ϊ "00"��
// uname�������ߵ��û�������null��β�ַ�����
// gname�������ߵ���������null��β�ַ�����
// devmajor���豸�ļ�����Ҫ�豸�ţ��԰˽����ַ�����ʾ��
// devminor���豸�ļ��Ĵ�Ҫ�豸�ţ��԰˽����ַ�����ʾ��
// prefix���ļ�����ǰ׺����null��β�ַ�����


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