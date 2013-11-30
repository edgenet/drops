#include "drops.h"

int main (int argc, char *argv [])
{
    if (argc < 2) {
        puts ("usage: dropsd directory");
        return 0;
    }
    printf ("dropsd I: monitoring '%s'...\n", argv [1]);
    drops_t *drops = drops_new (argv [1]);
    
    zpoller_t *poller = zpoller_new (drops_socket (drops), NULL);
    while (true) {
        void *which = zpoller_wait (poller, -1);
        if (which == drops_socket (drops)) {
            zmsg_t *msg = drops_recv (drops);
            zmsg_dump (msg);
            zmsg_destroy (&msg);
        }
        else
            break;
    }
    drops_destroy (&drops);
    return 0;
}
