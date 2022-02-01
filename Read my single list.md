# Hướng dẫn sử dụng Single List 💻
	Khai báo
	Các hàm hỗ trợ
	Các toán tử
	Iterator
	Bài tập áp dụng
	
# Khai báo :
	Tạo một danh sách rỗng kiểu int :
		SList<int> list;
	Tạo một danh sách mới từ danh sách cũ :
		SList<int> list2(list);

# Các hàm hỗ trợ :
	output				: xuất ra danh sách							⏲️ Time complexity : O(n)
	isEmpty				: kiểm tra danh sách rỗng						⏲️ Time complexity : O(1)
	length				: tính số phần tử trong danh sách					⏲️ Time complexity : O(1)
	getFront			: xem giá trị ở đầu danh sách						⏲️ Time complexity : O(1)
	getBack				: xem giá trị ở cuối danh sách						⏲️ Time complexity : O(1)
	swap				: hoán vị hai danh sách							⏲️ Time complexity : O(1)
	isFound				: kiểm tra có tồn tại một phần tử nào trong danh sách			⏲️ Time complexity : O(n)
	rotate				: đưa k phần tử ở đầu danh sách về cuối					⏲️ Time complexity : O(k % n)
	memset				: gán tất cả phần tử trong danh sách bằng một giá trị chỉ định		⏲️ Time complexity : O(n)
	reverse				: đảo danh sách								⏲️ Time complexity : O(n)
	sort				: sắp xếp danh sách							⏲️ Time complexity : O(n log(n))
	pushFront			: thêm một phần tử vào đầu danh sách					⏲️ Time complexity : O(1)
	pushBack			: thêm một phần tử vào cuối danh sách					⏲️ Time complexity : O(1)
	popFront, popFrontSecurity	: xóa một phần tử ở đầu danh sách					⏲️ Time complexity : O(1)
	popBack, popBackSecurity	: xóa một phần tử ở cuối danh sách					⏲️ Time complexity : O(n)
	
# Các toán tử :
	operator= 			: sao chép một danh sách						⏲️ Time complexity : O(n)
	operator+=			: nối một danh sách vào cuối						⏲️ Time complexity : O(n)
	operator+			: trả về một danh sách bằng tổng hai danh sách nối nhau			⏲️ Time complexity : O(n)
	
# Iterator : được hỗ trợ dùng để duyệt, sửa danh sách
	begin 				: trả về một iterator ở đầu danh sách					⏲️ Time complexity : O(1)
	last 				: trả về một iterator ở cuối danh sách					⏲️ Time complexity : O(1)
	end 				: trả về một iterator rỗng						⏲️ Time complexity : O(1)
	pop 				: xóa một phần tử tại iterator						⏲️ Time complexity : if iter is not last : O(1) then : O(n)
	popNext				: xóa một phần tử liền sau iterator					⏲️ Time complexity : O(1)
	pushPrev			: thêm một phần tử vào trước iterator					⏲️ Time complexity : O(1)
	pushNext			: thêm một vào tử vào sau iterator					⏲️ Time complexity : O(1)
	
# Bài tập áp dụng :
	📖📖📖 Đếm có bao nhiêu số chẵn trong danh sách
	
	int Count(SList<int>& A)
	{
		int count = 0;
		for(auto x : A)
			if(x % 2 == 0)
				count++;
		return count;
		//⏲️ Time complexity : O(n)
	}


	📖📖📖 Cho hai dãy A, B tăng dần. Hãy tạo dãy C cũng tăng dần từ hai dãy đã cho.
	Ví dụ : A { 1, 12, 17, 21 }, B { 0, 2, 5, 7, 7 }
	Output : C { 0, 1, 2, 5, 7, 7, 12, 17, 21 }
	
	void merge(SList<int>& A, SList<int>& B, SList<int>& C)
	{
		//Điều kiện : A, B tăng dần, C rỗng
		for (; !A.isEmpty() && !B.isEmpty();)
			if (A.getFront() <= B.getFront())
				C.pushBack(A.popFront());
			else
				C.pushBack(B.popFront());

		if (!A.isEmpty())
			C += A;
		if (!B.isEmpty())
			C += B;
		//⏲️ Time complexity : O(A.length() + B.length())
	}
		
		
	📖📖📖 Đếm số lượng các số đôi một khác nhau trong dãy gồm n phần tử
	Ví dụ : A { 0, 2, 3, 1, 0, 0, 3 }, n = 7
	Output : 4 gồm các phần tử { 0, 1, 2, 3 }
	
	int Count(SList<int>& A)
	{
		A.sort();

		int count = 0;
		auto iter = A.begin(), temp;

		while (!iter.isNull())	//or iter != A.end()
		{
			temp = iter;
			count++;
			while (!iter.isNull() && *iter != *temp)
				iter++;
		}
		return count;
		//⏲️ Time complexity : O(n log(n))
	}
