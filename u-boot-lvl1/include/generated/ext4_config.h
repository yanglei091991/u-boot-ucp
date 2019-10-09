#define CONFIG_JOURNALING_ENABLE 0
#define CONFIG_XATTR_ENABLE 0
#define CONFIG_EXTENTS_ENABLE 1
#define CONFIG_USE_USER_MALLOC 1
#define CONFIG_DEBUG_PRINTF 0
#define CONFIG_DEBUG_ASSERT 0

#include <stddef.h>
void *ext4_user_malloc(size_t size);
void *ext4_user_calloc(size_t nmemb, size_t size);
void ext4_user_free(void *ptr);
