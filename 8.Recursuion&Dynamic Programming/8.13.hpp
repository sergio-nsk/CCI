struct Box {
  int width;
  int height;
  int depth;
  bool canBeAbove(const Box& box) const {
    return width < box.width && height < box.height && depth < box.depth;
  }
};
