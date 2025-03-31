#ifndef POINT_COUNT_H
#define POINT_COUNT_H

typedef struct {
  double x;
  double y;
} point2d;

typedef struct {

} container;

container build_structure(const point2d* points, int n);

int get_inner_point_count(const container* container, point2d bl, point2d tr);

#endif //POINT_COUNT_H
