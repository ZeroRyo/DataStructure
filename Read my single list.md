# Hướng dẫn sử dụng Single List 💻
	- Khai báo
	- Các hàm hỗ trợ
	- Các toán tử
	- Iterator
	- Bài tập áp dụng
	
# Khai báo :
	- Tạo một danh sách rỗng kiểu int :
		SList<int> list;
	- Tạo một danh sách mới từ danh sách cũ :
		SList<int> list2(list);

# Các hàm hỗ trợ :
	- output : xuất ra danh sách
	- isEmpty : kiểm tra danh sách rỗng
	- length : tính số phần tử trong danh sách
	- getFront : xem giá trị ở đầu danh sách
	- getBack : xem giá trị ở cuối danh sách
	- swap : hoán vị hai danh sách
	- isFound : kiểm tra có tồn tại một phần tử nào trong danh sách
	- rotate : đưa k phần tử ở đầu danh sách về cuối
	- memset : gán tất cả phần tử trong danh sách bằng một giá trị chỉ định
	- reverse : đảo danh sách
	- sort : sắp xếp danh sách
	- pushFront : thêm một phần tử vào đầu danh sách
	- pushBack : thêm một phần tử vào cuối danh sách
	- popFront, popFrontSecurity : xóa một phần tử ở đầu danh sách
	- popBack, popBackSecurity : xóa một phần tử ở cuối danh sách
	
# Các toán tử :
	- operator= : sao chép một danh sách
	- operator+= : nối một danh sách vào cuối
	- operator+ : trả về một danh sách bằng tổng hai danh sách nối nhau
	
# Iterator : được hỗ trợ dùng để duyệt, sửa danh sách
	- begin : trả về một iterator ở đầu danh sách
	- last : trả về một iterator ở cuối danh sách
	- end : trả về một iterator rỗng
	- pop : xóa một phần tử tại iterator
	- popNext : xóa một phần tử liền sau iterator
	- pushPrev : thêm một phần tử vào trước iterator
	- pushNext : thêm một vào tử vào sau iterator
	
# Bài tập áp dụng :
	- Cho hai dãy A, B tăng dần. Hãy tạo dãy C cũng tăng dần từ hai dãy đã cho.
	Ví dụ : A { 1, 12, 17, 21 }, B { 0, 2, 5, 7, 7 }
	Output : C { 0, 1, 2, 5, 7, 7, 12, 17, 21 }
	
		void merge(SList<int>& A, SList<int>& B, SList<int>& C)
		{
			//Điều kiện : A, B tăng dần, C rỗng
			for(; !A.isEmpty() && !B.isEmpty();)
				if(A.getFront() <= B.getFront())
					C.pushBack(A.popFront());
				else
					C.pushBack(B.popFront());
			
			if(!A.isEmpty())
				C += A;
			if(!B.isEmpty())
				C += B;
			//Time complexity : O(A.length() + B.length())
		}
		
		
	- Đếm số lượng các số đôi một khác nhau trong dãy gồm n phần tử
	Ví dụ : A { 0, 2, 3, 1, 0, 0, 3 }, n = 7
	Output : 4 gồm các phần tử { 0, 1, 2, 3 }
	
		int count(SList<int>& A)
		{
			A.sort();
			
			int count = 0;
			auto iter = A.begin(), temp;
			
			while(!iter.isNull())	//or iter != A.end()
			{
				temp = iter;
				count++;
				while(!iter.isNull() && *iter != *temp)
					iter++;
			}
			return count;
			//Time complexity : O(n log(n))
		}
