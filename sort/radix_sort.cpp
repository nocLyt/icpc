// Radix sort
// BASE 进制数
void radix_sort(vector<int> &a, const int BASE){
	int len = a.size();
	if (len == 0)
		return ;
	int exp = 1, b[len], mx = a[0];	// exp 指数
	for (int i=0; i<len; i++)
		mx = max(mx, a[i]);

	int times = 0;
	while( mx/exp >0){
		int buket[BASE];
		for (int i=0; i<BASE; i++)
			buket[i] = 0;

		for (int i=0; i<len; i++)
			buket[(a[i]/exp)%BASE] ++;

		for (int i=1; i<BASE; i++)
			buket[i] += buket[i-1];

		for (int i=len-1; i>=0; i--){
			b[--buket[(a[i]/exp)%BASE]] = a[i];
		}

		for (int i=0; i<len; i++)
			a[i] = b[i];
		exp *= BASE;
		
	}

}
