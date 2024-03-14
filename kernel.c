#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
#if defined(__linux__)
#error "You are not using a cross-compiler"
#endif
 
#if !defined(__i386__)
#error "Use an ix86-elf compiler please"
#endif

#define COLOR 0x07 // fg,bg: white,black
#define BLINK 0x87 // blink effect
#define VGA_WIDTH 80
#define VGA_HEIGHT 25


void k_clear_screen()
{
  char *vidmem = (char *) 0xB8000;
  unsigned int index = 0;
  while (index < (VGA_WIDTH * VGA_HEIGHT * 2)) {
    vidmem[index] = ' ';
    index++;
    vidmem[index] = COLOR;
    index++;
  }
}

void k_print(char *text, unsigned int line)
{
  char *vidmem = (char *) 0xB8000;
  unsigned int index = 0;
  index = (line * VGA_WIDTH * 2);
  while (*text != 0) {
    switch (*text) {
    case '\n':
      line++;
      index = (line * VGA_WIDTH * 2);
      *text++;
      break;
      
    default:
      vidmem[index] = *text;
      index++;
      vidmem[index] = COLOR;
      index++;
      *text++;
      break;
    }
  }
}

void k_update_cursor(unsigned int col, unsigned int row)
{
  unsigned int index = (col + row * VGA_WIDTH) * 2;
  char *vidmem = (char *) 0xB8000;
  vidmem[index] = '|';
  vidmem[index+1] = BLINK;
}

size_t k_strlen(char *str)
{
  unsigned int len = 0;
  while (str[len]) {
    len++;
  }
  return len;
}

void kernel_main(void)
{
  unsigned int line = 0;
  char *message = "Hello from FTC kernel !!";
  k_clear_screen();
  k_print(message, line);
  k_update_cursor(k_strlen(message), line);
}
