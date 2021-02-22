#include "algorithm_test.h"
#include "hldb_log.h"

int main() {
  hldb_log_init();
  hldb_log_set_target_by_str("file");
  RUN_ALL_TESTS();
}