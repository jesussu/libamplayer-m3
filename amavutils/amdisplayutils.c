
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>
#include <sys/ioctl.h>
#include "include/Amdisplayutils.h"

#define FB_DEVICE_PATH   "/sys/class/graphics/fb0/virtual_size"
#define SCALE_AXIS_PATH  "/sys/class/graphics/fb0/scale_axis"
#define SCALE_PATH       "/sys/class/graphics/fb0/scale"
#define SCALE_REQUEST 	 "/sys/class/graphics/fb0/request2XScale"
#define SYSCMD_BUFSIZE 40

int amdisplay_utils_get_size(int *width, int *height)
{
    char buf[SYSCMD_BUFSIZE];
    int disp_w = 0;
    int disp_h = 0;
    int ret;
    ret = amsysfs_get_sysfs_str(FB_DEVICE_PATH, buf, SYSCMD_BUFSIZE);
    if (ret < 0) {
        return ret;
    }
    if (sscanf(buf, "%d,%d", &disp_w, &disp_h) == 2) {
        disp_h = disp_h / 2;
    } else {
        return -2;/*format unknow*/
    }
    *width = disp_w;
    *height = disp_h;
    return 0;
}


int amdisplay_utils_set_scale_mode(int scale_wx, int scale_hx)
{
    int width, height;
    int ret;
    int neww, newh;
    char buf[40];

    /*scale mode only support x2,x1*/
    if ((scale_wx != 1 && scale_wx != 2) || (scale_hx != 1 && scale_hx != 2)) {
        return -1;
    }
	if(scale_wx==2)
	    ret = amsysfs_set_sysfs_str(SCALE_REQUEST, "1");
	else if(scale_wx==1)
	    ret = amsysfs_set_sysfs_str(SCALE_REQUEST, "2");   
	     
    if (ret < 0) {
        return -2;
    }
    return ret;
}


