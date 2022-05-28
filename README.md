# Snake Game 
1. Hướng dẫn cài đặt
  - Bước 1: Vào phần Code -> chọn Download ZIP
  ![image](https://user-images.githubusercontent.com/100121918/170812450-ccab6c04-b593-4ff4-b430-a43a938efb96.png)
  - Bước 2: Giải nén file ZIP -> tìm file Snake.exe trong folder x64/Release và chạy. ![image](https://user-images.githubusercontent.com/100121918/170807682-8647dc0b-d230-4814-a567-ba2671ba71f0.png)

  - Bước 3: Trải nghiệm game

2. Mô tả chung:
- Ý tưởng: giống game rắn cổ điển 
- Hướng dẫn chơi: 
  + Sử dụng các phím  ← → ↑ ↓  hoặc 2 4 6 8 để di chuyển con rắn đến vị trí quả táo để ăn 
  + Sử dụng phím Space để stop, nhấn các phím mũi tên di chuyển để tiếp tục
  + Mỗi khi ăn quả táo, rắn sẽ dài thêm 1 đốt và quả táo mới xuất hiện ở vị trí khác
  + Mỗi khi con rắn dài thêm 3 đốt, tốc độ di chuyển của con rắn sẽ nhanh hơn và xuất hiện thêm một cây nấm ở vị trí ngẫu nhiên
  + Nếu ăn phải cây nấm, thân con rắn ngắn đi 3 đốt đồng thời điểm sẽ bị trừ đi 30 điểm
  + Nếu đâm vào khung, rắn sẽ chết -> màn hình Game over xuất hiện, hiện điểm cao nhất đã đạt được và điểm hiện tại -> Enter để bắt đầu lại 
  + Link youtube demo game: [https://youtu.be/tXLr3Br-EQM](https://youtu.be/6nb6ngSIHbo)
3. Game sử dụng các kiến thức:
  + Mảng vector
  + Bắt sự kiện bàn phím
  + Sinh số ngẫu nhiên  
  + Xử lí va chạm
 4. Kết luận
  + Bản thân em qua quá trình làm game đã rút ra được một số kinh nghiệm lập trình như logic, biết cách tìm và sửa lỗi,... Em thấy thư viện đồ họa SDL khá đơn giản và dễ sử dụng, có sẵn nhiều hàm tiện dụng, rất thích hợp và là lựa chọn tốt cho những người mới học về đồ họa.
  + Hướng phát triển: Em sẽ viết thêm một số tùy chọn như chế độ 2 người cùng chơi, thêm chướng ngại vật, thêm nhiều level...
  
