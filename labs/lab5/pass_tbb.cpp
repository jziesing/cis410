#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <tbb/tbb.h>
#include <openssl/md5.h>
using namespace tbb;
const char* chars="0123456789";
// tests if a hash matches a candidate password
int test(const char* passhash, const char* passcandidate) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    
    MD5((unsigned char*)passcandidate, strlen(passcandidate), digest);
    
    char mdString[34];
    mdString[33]='\0';
    for(int i=0; i<16; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned char)digest[i]);
    }
    return strncmp(passhash, mdString, strlen(passhash));
}

// maps a PIN to a string
void genpass(long passnum, char* passbuff) {
    passbuff[8]='\0';
    int charidx;
    int symcount=strlen(chars);
    for(int i=7; i>=0; i--) {
        charidx=passnum%symcount;
        passnum=passnum/symcount;
        passbuff[i]=chars[charidx];
    }
}

class Ploop {
	char *const argv;
	public:
		void operator() ( const blocked_range<int>&length ) const {
			for(int i=length.begin(); i!=length.end(); i++) {
				char passmatch[9];
				long currpass = 0;
				int notfound = 1;
				genpass(currpass,passmatch);
				notfound = test(argv, passmatch);
				if(notfound == 0) {
					printf("found: %s\n", passmatch);
				}
				currpass++;	
			}
		}
		Ploop(char* test) : argv(test){
		}
};

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: %s <password hash>\n",argv[0]);
        return 1;
    }
	/*
    char passmatch[9];
    long currpass=0;
    int notfound=1;
    while(notfound) {
        genpass(currpass,passmatch);
        notfound=test(argv[1], passmatch);
        currpass++;
    }
    printf("found: %s\n",passmatch);
   */
	Ploop test(argv[1]);
	tbb::parallel_for(blocked_range<int>(0, 100000000), test);
	return 0;
}
