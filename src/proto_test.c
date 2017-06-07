#include <stdio.h>

#include <include/uhp.h>
int
main()
{
        struct transaction *transac_table[MAX_PORT];
        int i;

        init_table(transac_table, MAX_PORT);

        for (i = 0; i < MAX_PORT; i++) {
                if ( transac_table[i] == NULL)
                        printf("NOT INITIALIZED\n");
        }

        return 0;
}
