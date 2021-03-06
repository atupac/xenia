/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <xenia/kernel/fs/devices/host_path_device.h>

#include <xenia/kernel/fs/devices/host_path_entry.h>
#include <xenia/kernel/objects/xfile.h>

namespace xe {
namespace kernel {
namespace fs {

HostPathDevice::HostPathDevice(const std::string& path,
                               const std::wstring& local_path)
    : Device(path), local_path_(local_path) {}

HostPathDevice::~HostPathDevice() {}

std::unique_ptr<Entry> HostPathDevice::ResolvePath(const char* path) {
  // The filesystem will have stripped our prefix off already, so the path will
  // be in the form:
  // some\PATH.foo

  XELOGFS("HostPathDevice::ResolvePath(%s)", path);

  auto rel_path = poly::to_wstring(path);
  auto full_path = poly::join_paths(local_path_, rel_path);
  full_path = poly::fix_path_separators(full_path);

  // TODO(benvanik): get file info
  // TODO(benvanik): fail if does not exit
  // TODO(benvanik): switch based on type

  auto type = Entry::Type::FILE;
  return std::make_unique<HostPathEntry>(type, this, path, full_path);
}

}  // namespace fs
}  // namespace kernel
}  // namespace xe
