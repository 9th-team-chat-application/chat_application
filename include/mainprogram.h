#ifndef __MAINPROGRAM_H__
#define __MAINPROGRAM_H__

void auto_update_thread();
gboolean do_connect(void);
void *Front(Queue Q);
void MakeEmpty(Queue Q);

#endif