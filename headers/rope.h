#ifndef ROPE_H
#define ROPE_H

typedef struct {

} rope;

typedef struct {
  rope r1;
  rope r2;
} rope_tuple;

rope build_rope(const char* str);

void iterate_rope(rope rope, void (*callback)(char));

char rope_get_at(rope rope, int i);

rope_tuple split_rope(rope rope, int i);

rope concatenate_ropes(rope rope1, rope rope2);

rope rope_substring(rope rope, int i, int n);

rope rope_cut(rope rope, int i, int n);

rope rope_insert_at(rope src, int i, rope to_insert);

#endif //ROPE_H
