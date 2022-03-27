#include <jagdefs.h>
#include <jagtypes.h>
#include <stdlib.h>

#include <interrupt.h>
#include <display.h>
#include <sprite.h>

#include <sound.h>

#include <joypad.h>

#include <console.h>

extern phrase image;
extern phrase hl;

#define IMGW 320
#define IMGH 240

int dir;
int main(int argc, char *argv[]) {
  TOMREGS->vmode = CRY16|CSYNC|BGEN|PWIDTH4|VIDEN;
  init_interrupts();
  init_display_driver();

  display *d = new_display(0);
  d->x = 16;
  d->y = 8;

  dir = 0;

  show_display(d);

  sprite *s = new_sprite(IMGW,IMGH,0,0,DEPTH16,&image);
  sprite *s2 = new_sprite(32,32,160-16,120-16,DEPTH16,&hl);
  s2->rmw = 1;

  attach_sprite_to_display_at_layer(s,d,1);
  attach_sprite_to_display_at_layer(s2,d,3);

  while(1) {
    vsync();
    if (dir == 0) {
      if (++s2->x >= 320-16) {
        dir = 1;
      }
    } else if (dir == 1) {
      if (--s2->x <= -16) {
        dir = 0;
      }
    }
  }

  return 0;
}

