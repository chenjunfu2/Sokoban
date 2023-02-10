#include "error.h"

//´íÎó
extern inline void no_good(ERR& error, unsigned err_num, unsigned err_fun, unsigned err_msg)
{
	error.no_good = true;
	error.err_num = err_num;
	error.err_fun = err_fun;
	error.err_msg = err_msg;
}
//³·Ïú´íÎó
extern inline void are_good(ERR& error)
{
	error.no_good = false;
	error.err_num = GOOD_ERR;
	error.err_fun = 0x0000;
}

//±¨´íº¯Êý
extern inline bool error(ERR error)
{
	if (error.no_good == false || error.err_num == GOOD_ERR)
		return false;

	fprintf(stderr, "\nERROR:\n");
	fprintf(stderr, "FUNTION_CODE=0x%04X ERROR_CODE=0x%04X\nERROR_MESSAGE=%06d ERROR_REASON=%s\n\n",
		error.err_fun, error.err_num, error.err_msg, reason[error.err_num]);

	return error.no_good;
}
