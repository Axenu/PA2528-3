#include "Future.hpp"

namespace FuturePrivate {


void entry(void* block) {
    Block* b = (Block*)block;
    b->ret = b->function(b->args);
}
}
