#include <check.h>
#include <kfs_create.h>
#include <kfs_write.h>
#include <kfs_open.h>
#include <kfs_read.h>
#include <kfs_ftruncate.h>

#include "test_main.h"

void kfs_ftruncate_setup(void) {
    main_setup();
}

void kfs_ftruncate_teardown(void) {
    main_teardown();
}

START_TEST(kfs_ftruncate_increase_size_of_exist_file) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("exist.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "exist.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = {O_RDWR};
    res = kfs_open(path, &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write(path,buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    char *new_buf = "qwery000000000000\n";
    res = kfs_ftruncate(path, strlen(new_buf), &fi);
    ck_assert_int_eq(res,0);
    char buf_read [strlen(new_buf)];
    res = kfs_read(path, buf_read, strlen(new_buf), 0, &fi);
    ck_assert_int_eq(res, strlen(new_buf));
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_ftruncate_decrease_size_of_exist_file) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("exist.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "exist.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = {O_RDWR};
    res = kfs_open(path, &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write(path,buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    char *new_buf = "q\n";
    res = kfs_ftruncate(path, strlen(new_buf), &fi);
    ck_assert_int_eq(res,0);
    char buf_read [strlen(new_buf)];
    res = kfs_read(path, buf_read, strlen(new_buf), 0, &fi);
    ck_assert_int_eq(res, strlen(new_buf));
    close(create.fh);
    close(fi.fh);
}
END_TEST

Suite *kfs_ftruncate_suite(void) {
    Suite *suite = suite_create("kfs_ftruncate()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_ftruncate_setup, kfs_ftruncate_teardown);
    tcase_add_test(tcase, kfs_ftruncate_increase_size_of_exist_file);
    tcase_add_test(tcase, kfs_ftruncate_decrease_size_of_exist_file);
    suite_add_tcase(suite, tcase);
    return suite;
}