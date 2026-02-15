
int find(int *v, int size) {
    int left = 0;
    int right = size - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (v[mid] == v[mid ^ 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return v[left];
}

int main() {
    int v[] = {1,1,2,3,3};
    
    int ret = find(v, sizeof(v)/4);
    printf("ret=%d\n", ret); // ret=2
    
    return 0;
}
