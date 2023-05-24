mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout << setprecision(15) << fixed;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")