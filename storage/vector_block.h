/**
 * Copyright 2019 The Gamma Authors.
 *
 * This source code is licensed under the Apache License, Version 2.0 license
 * found in the LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <stdint.h>
#include <unistd.h>
#include <vector>

#include "block.h"
#include "lru_cache.h"



typedef uint32_t str_offset_t;
typedef uint16_t str_len_t;

namespace tig_gamma {


class VectorBlock : public Block {
 public:
  VectorBlock(int fd, int per_block_size, int length, uint32_t header_size,
              uint32_t seg_id, uint32_t seg_block_capacity,
              const std::atomic<uint32_t> *cur_size, int max_size);

  static bool ReadBlock(uint32_t key, char *block,
                        ReadFunParameter *param);

  int WriteContent(const uint8_t *data, int len, uint32_t offset,
                   disk_io::AsyncWriter *disk_io,
                   std::atomic<uint32_t> *cur_size) override;

  int ReadContent(uint8_t *value, uint32_t len, uint32_t offset) override;

  int Read(uint8_t *value, uint32_t len, uint32_t offset) override;

  int Update(const uint8_t *data, int n_bytes, uint32_t offset) override;

 private:
  void InitSubclass() override;

  int GetReadFunParameter(ReadFunParameter &parameter, uint32_t len,
                          uint32_t off) override;

  int Compress(const uint8_t *data, int len, std::vector<char> &output);

  int vec_item_len_;
};

}  // namespace tig_gamma
