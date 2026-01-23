#include <stdio.h>
#include <string.h>

int main() {
    char *str = "Hello";  // String literal (read-only memory)
    
    printf("String: %s\n", str);  // OK - reading
    
    str[0] = 'h';  // ✗ CRASH! Writing to read-only memory
    
    return 0;
}
