# Snake Game 
> Họ và tên: Đinh Thị Mai Linh - K66CD 
> 
> Mã số sinh viên: 21020773
>
**1. Hướng dẫn cài đặt (trên Visual Studio)**
  - __Bước 1:__ Vào phần Code -> chọn Download ZIP
  ![image](https://user-images.githubusercontent.com/100121918/170812450-ccab6c04-b593-4ff4-b430-a43a938efb96.png)
  - __Bước 2:__ Giải nén file ZIP -> tìm và mở file Snake.sln ![image](https://user-images.githubusercontent.com/100121918/171084478-fa9a93bd-583f-4ff3-8e1f-655f5e9c5434.png)

  - __Bước 3:__ Vào Project -> Snake properties
    + Trong VC++Directories/Include Directories -> chọn edit và thêm lần lượt từng đường dẫn sau:
      - $(SolutionDir)LibSdl2\SDL2_ttf-2.0.14\include
      - $(SolutionDir)LibSdl2\SDL2_mixer-2.0.2\include
      - $(SolutionDir)LibSdl2\SDL2-2.0.8\include
      
    _Làm tương tự với phần VC++Directories/Library Directories và Linker/Input/Additional Dependencies bên dưới_
    + VC++Directories/Library Directories:
      - $(SolutionDir)LibSdl2\SDL2-2.0.8\lib\x64
      - $(SolutionDir)LibSdl2\SDL2_mixer-2.0.2\lib\x64
      - $(SolutionDir)LibSdl2\SDL2_ttf-2.0.14\lib\x64
    + Linker/Input/Additional Dependencies:
      - SDL2.lib
      - SDL2main.lib
      - SDL2_mixer.lib
      - SDL2_ttf.lib
   - __Bước 4:__ Nhấn Ctrl + F5 để chạy chương trình.
  
**2. Mô tả chung:**
- _Ý tưởng:_ giống game rắn cổ điển 
- _Hướng dẫn chơi:_ 
  + Sử dụng các phím ⬅⬇⬆➡ hoặc 2 4 6 8 để di chuyển con rắn đến vị trí quả táo để ăn 
  + Sử dụng phím Space để tạm dừng, nhấn các phím mũi tên di chuyển để tiếp tục
  + Mỗi khi ăn quả táo, rắn sẽ dài thêm 1 đốt và quả táo mới xuất hiện ở vị trí khác
  + Mỗi khi con rắn dài thêm 3 đốt, tốc độ di chuyển của con rắn sẽ nhanh hơn và xuất hiện thêm một cây nấm ở vị trí ngẫu nhiên
  + Nếu ăn phải cây nấm, thân con rắn ngắn đi 3 đốt đồng thời điểm sẽ bị trừ đi 30 điểm
  + Nếu đâm vào khung, rắn sẽ chết -> màn hình Game over xuất hiện, hiện điểm cao nhất đã đạt được và điểm hiện tại -> Enter để bắt đầu lại 
  + Link youtube demo game: [https://youtu.be/tXLr3Br-EQM](https://youtu.be/6nb6ngSIHbo)
  
**3. Game sử dụng các kiến thức:**
  + Mảng vector
  + Bắt sự kiện bàn phím
  + Sinh số ngẫu nhiên 
    - Sinh ra vị trí ngẫu nhiên cho quả táo và cây nấm sao cho không trùng với vật thể nào đã có  
  + Xử lí va chạm
    - Va chạm giữa con rắn và khung
    - Va chạm giữa con rắn và thân nó
    - Va chạm giữa con rắn và quả táo /cây nấm 
  
**4. Kết luận:**
  + Bản thân em qua quá trình làm game đã rút ra được một số kinh nghiệm lập trình như logic, biết cách tìm và sửa lỗi,... Em thấy thư viện đồ họa SDL khá đơn giản và dễ sử dụng, có sẵn nhiều hàm tiện dụng, rất thích hợp và là lựa chọn tốt cho những người mới học về lập trình đồ họa.
  + Hướng phát triển: 
    + Em sẽ viết thêm một số mục như: 
      - Menu bao gồm hướng dẫn chơi và các tùy chọn của game
      - Chế độ 2 người cùng chơi
      - Thêm chướng ngại vật, thêm nhiều level
      - Thêm nhiều hình ảnh, âm thanh hơn để game thêm sinh động
    + Về phần code em sẽ cố gắng tối ưu hơn, sửa để code gọn gàng hơn, tách file,..
  
