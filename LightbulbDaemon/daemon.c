/*
Adapted for use as a daemon for RFID-based computing with the project Lightbulb by Peter Hajas (www.peterhajas.com) for RCOS 2009.
 
 http://rcos.cs.rpi.edu/
 
Lightbulb Team:
 Peter Hajas
 Aileen Sheedy
 Michael O'Keefe
 
Licensed under the BSD License.
 
 The current version of this code, as of this writing (October 1st, 2009) is Mac-only.. Please adapt the RFID tags/system calls as you see fit. 
 A storage system for tags will be added in the coming days to make this code more versatile. This is a proof of concept only.

Originally written by Tod E. Kurt, the copyright has been preserved below.
 
Thanks to Sean O'Sullivan for the sponsorship. 

 //Original Copyright, check out Tod's site, he's a very smart guy!
 * Created 5 December 2006
 * Copyleft (c) 2006, Tod E. Kurt, tod@todbot.com
 * http://todbot.com/blog/
 */

#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h> 
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>

int serialport_init(const char* serialport, int baud);
int serialport_writebyte(int fd, uint8_t b);
int serialport_write(int fd, const char* str);
int serialport_read_until(int fd, char* buf, char until);
int compare(char* one, char*two);

int main(int argc, char *argv[]) 
{
    int fd = 0;
    char serialport[] = "/dev/tty.usbserial-A9007KDB";
    int baudrate = B9600;  // default
    char buf[10];
    int rc,n;
	while(1)
	{
		fd = serialport_init(serialport, baudrate);
		serialport_read_until(fd, buf, '\n');
		printf("%s",buf);
		if(compare(buf,"23006EB03E") == 1)
		{
			system("open -a /Applications/Stickies.app/");
		}
		if(compare(buf,"23006F7D4D") == 1)
		{
			system("open -a /Applications/Chess.app/");
		}
		if(compare(buf,"23006EAF5A") == 1)
		{
			system("open http://news.google.com");
		}
	}
	
    return 0;    
} // end main

int compare(char* one, char*two)
{
	int i;
	//This assumes the character strings are 10 characters long. It compares the two, and returns "1" if they are the same and "0" if they are different
	for(i = 0; i < 10; i++)
	{
		if(one[i] != two[i])
		{
			return 0;
		}
	}
	return 1;
}

int serialport_writebyte( int fd, uint8_t b)
{
    int n = write(fd,&b,1);
    if( n!=1)
        return -1;
    return 0;
}

int serialport_write(int fd, const char* str)
{
    int len = strlen(str);
    int n = write(fd, str, len);
    if( n!=len ) 
        return -1;
    return 0;
}

int serialport_read_until(int fd, char* buf, char until)
{
    char b[1];
    int i=0;
    do { 
        int n = read(fd, b, 1);  // read a char at a time
        if( n==-1) return -1;    // couldn't read
        if( n==0 ) {
            usleep( 10 * 1000 ); // wait 10 msec try again
            continue;
        }
        buf[i] = b[0]; i++;
    } while( b[0] != until );
	
    buf[i] = 0;  // null terminate the string
    return 0;
}

// takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1")
// and a baud rate (bps) and connects to that port at that speed and 8N1.
// opens the port in fully raw mode so you can send binary data.
// returns valid fd, or -1 on error
int serialport_init(const char* serialport, int baud)
{
    struct termios toptions;
    int fd;
    
    //fprintf(stderr,"init_serialport: opening port %s @ %d bps\n",
    //        serialport,baud);
	
    fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)  {
        perror("init_serialport: Unable to open port ");
        return -1;
    }
    
    if (tcgetattr(fd, &toptions) < 0) {
        perror("init_serialport: Couldn't get term attributes");
        return -1;
    }
    speed_t brate = baud; // let you override switch below if needed
    switch(baud) {
		case 4800:   brate=B4800;   break;
		case 9600:   brate=B9600;   break;
#ifdef B14400
		case 14400:  brate=B14400;  break;
#endif
		case 19200:  brate=B19200;  break;
#ifdef B28800
		case 28800:  brate=B28800;  break;
#endif
		case 38400:  brate=B38400;  break;
		case 57600:  brate=B57600;  break;
		case 115200: brate=B115200; break;
    }
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);
	
    // 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    // no flow control
    toptions.c_cflag &= ~CRTSCTS;
	
    toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
	
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw
	
    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 20;
    
    if( tcsetattr(fd, TCSANOW, &toptions) < 0) {
        perror("init_serialport: Couldn't set term attributes");
        return -1;
    }
	
    return fd;
}
