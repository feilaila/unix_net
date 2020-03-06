#include	"ping.h"
int main(int argc, char **argv)
{
    /* code */
    int				c;
	struct addrinfo	*ai;
    char *h;

	opterr = 0;		/* don't want getopt() writing to stderr */
    while ( (c = getopt(argc, argv, "v")) != -1) {
		switch (c) {
		case 'v':
			verbose++;
			break;

		case '?':
			err_quit("unrecognized option: %c", c);
		}
	}
    if (optind != argc-1)
		err_quit("usage: ping [ -v ] <hostname>");
	host = argv[optind];
    pid = getpid() & 0xffff;	/* ICMP ID field is 16 bits */
    Signal(SIGALRM, sig_alrm);
    printf("ssssk %d",pid);

    return 0;
}
