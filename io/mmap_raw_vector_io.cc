#include "mmap_raw_vector_io.h"

#include "error_code.h"
#include "io_common.h"

namespace tig_gamma {

int MmapRawVectorIO::Init() { return 0; }

int MmapRawVectorIO::Dump(int start_vid, int end_vid) {
  int ret = raw_vector->storage_mgr_->Sync();
  LOG(INFO) << "MmapRawVector sync, doc num["
            << raw_vector->storage_mgr_->Size() << "]";
  return ret;
}

int MmapRawVectorIO::Load(int vec_num) {
  if (raw_vector->storage_mgr_->Truncate(vec_num)) {
    LOG(ERROR) << "truncate gamma db error, vec_num=" << vec_num;
    return INTERNAL_ERR;
  }
  raw_vector->MetaInfo()->size_ = vec_num;
  LOG(INFO) << "mmap load success! vec num=" << vec_num;
  return 0;
}

int MmapRawVectorIO::Update(int vid) {
  return 0;  // do nothing
}

}  // namespace tig_gamma
