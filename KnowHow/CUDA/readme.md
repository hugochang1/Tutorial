### TODO
```
#define ELOG(msg)                                                      \
    printf("[ERR] %s %s() line:%d msg=[%s]\n", __FILE__, __func__, __LINE__, msg);
```
### 設定 env CUDA_LOG_FILE=cudaLog.txt
- 在方案總管中，對你的專案按滑鼠右鍵，選擇 屬性 (Properties)
- 在左側選單依序展開：組態屬性 (Configuration Properties) -> 偵錯 (Debugging)
- 找到右側的 環境 (Environment) 欄位，點擊該欄位右邊的下拉箭頭，選擇 <編輯...>
- CUDA_LOG_FILE=cudaLog.txt
