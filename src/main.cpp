// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

/**
 * @file
 * @brief Application that consumes the Azure SDK for C++.
 *
 * @remark Set environment variable `STORAGE_CONNECTION_STRING` before running the application.
 *
 */
#include <azure/storage/blobs.hpp>
#include <fmt/core.h>

#include <exception>
#include <iostream>
#include <vector>
#include <memory>

using namespace Azure::Storage::Blobs;
using namespace Azure::Storage;

int main(int argc, char* argv[])
{
  std::string account("vamosaprobar");
  std::string endpoint("https://vamosaprobar.blob.core.windows.net");
  std::string bucket("deltalake");
  std::string secret("qVOrNkZgVD1DNxUa+zi9/j/gj+zYzwwmhpvj8JFa5nrrmsE5kEbhrUnRCMxwHxOeQxsBA2RVkbFG+AStj4jWJw==");
  std::string pathToFile("aver/tent.pdf");
  auto sharedKeyCredential = std::make_shared<StorageSharedKeyCredential>(account, secret);
  auto blobClient = std::make_shared<BlobContainerClient>(
      fmt::format("{0}/{1}", endpoint, bucket), sharedKeyCredential);
  auto bbc = blobClient->GetBlockBlobClient(pathToFile);
  auto b = std::make_unique<std::vector<uint8_t>>(1024 * 1024);
  auto res = bbc.DownloadTo(b->data(), b->size());
  std::cout << std::string(b->begin(), b->end());

  return 0;
}
