#include "list_persistent.h"
#include <stdlib.h>

list_persistent create_empty() {
    list_persistent result = {.head = NULL, .version = 0};
    return result;
}