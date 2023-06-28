// Copyright (c) 2012 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include <cstdio>
#include <iostream>

#include "leveldb/dumpfile.h"
#include "leveldb/env.h"
#include "leveldb/status.h"
#include "leveldb/db.h"

namespace leveldb {
namespace {

class StdoutPrinter : public WritableFile {
 public:
  Status Append(const Slice& data) override {
    fwrite(data.data(), 1, data.size(), stdout);
    return Status::OK();
  }
  Status Close() override { return Status::OK(); }
  Status Flush() override { return Status::OK(); }
  Status Sync() override { return Status::OK(); }
};

bool HandleDumpCommand(Env* env, char** files, int num) {
  StdoutPrinter printer;
  bool ok = true;
  for (int i = 0; i < num; i++) {
    Status s = DumpFile(env, files[i], &printer);
    if (!s.ok()) {
      std::fprintf(stderr, "%s\n", s.ToString().c_str());
      ok = false;
    }
  }
  return ok;
}

}  // namespace
}  // namespace leveldb

static void Usage() {
  std::fprintf(
      stderr,
      "Usage: leveldbutil command...\n"
      "   dump files...         -- dump contents of specified files\n");
}

int main(int argc, char** argv) {
    /*
  leveldb::Env* env = leveldb::Env::Default();
  bool ok = true;
  if (argc < 2) {
    Usage();
    ok = false;
  } else {
    std::string command = argv[1];
    if (command == "dump") {
      ok = leveldb::HandleDumpCommand(env, argv + 2, argc - 2);
    } else {
      Usage();
      ok = false;
    }
  }*/

    leveldb::DB* db = nullptr;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "D:\\testdb", &db);
    if (!status.ok()) {
        std::cout << status.ToString() << std::endl;
        return 1;
    }
    std::string value;

	

	/*
    time_t now = time(NULL);
    for (int i = 0; i < 10000; ++i) {
        char buff[64];
        int r = snprintf(buff, sizeof(buff), "key%d", i);
        buff[r] = 0;
        db->Put(leveldb::WriteOptions(), buff, "value", now + i);
    }*/

    

    //db->CompactRange(NULL, NULL);
	
    for (int i = 0; i < 10000; ++i) {
        char buff[64];
        int r = snprintf(buff, sizeof(buff), "key%d", i);
        buff[r] = 0;
        status = db->Get(leveldb::ReadOptions(), buff, &value);
        if (status.ok()) {
            std::cout << "×îÐ¡Öµ" << buff << "=" << value << std::endl;
            break;
        }
    }

	/*
    status = db->Get(leveldb::ReadOptions(), "key1", &value);
    if (status.ok()) {
        std::cout << value << std::endl;
    } else {
        std::cout << status.ToString() << std::endl;
    }*/
    delete db;
    return 0;
}
