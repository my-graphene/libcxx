//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <memory>

#include "benchmark/benchmark_api.h"

static void BM_SharedPtrCreateDestroy(benchmark::State& st) {
  while (st.KeepRunning()) {
    auto sp = std::make_shared<int>(42);
    benchmark::DoNotOptimize(sp.get());
  }
}
BENCHMARK(BM_SharedPtrCreateDestroy);

static void BM_SharedPtrIncDecRef(benchmark::State& st) {
  auto sp = std::make_shared<int>(42);
  benchmark::DoNotOptimize(sp.get());
  while (st.KeepRunning()) {
    std::shared_ptr<int> sp2(sp);
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_SharedPtrIncDecRef);

static void BM_WeakPtrIncDecRef(benchmark::State& st) {
  auto sp = std::make_shared<int>(42);
  benchmark::DoNotOptimize(sp.get());
  while (st.KeepRunning()) {
    std::weak_ptr<int> wp(sp);
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_WeakPtrIncDecRef);

BENCHMARK_MAIN()
