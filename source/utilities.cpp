#include "../include/utilities.hpp"

struct HtmlNames {
	const char* folder = "html_log_eblan/";
	HtmlFile files[1] = { {.file_name = "main.html"} };
} Log_Names;

StackStatusCode MakeHtmlFolder(Stack_t* stk) {

	StackStatusCode status = STACK_NO_ERROR;

	char* make_folder = NULL;
	status = StrConcatenation("mkdir ", Log_Names.folder, &make_folder, stk);
	STACK_ERROR_CHECK(status, stk);

	system(make_folder);
	if (make_folder)
		free(make_folder);

	return STACK_NO_ERROR;
}

StackStatusCode MakeHtmlFilePath(Stack_t* stk) {

	StackStatusCode status = STACK_NO_ERROR;

	size_t size = sizeof(Log_Names.files) / sizeof(Log_Names.files[0]);

	for (size_t i = 0; i < size; i++) {
		status = StrConcatenation(Log_Names.folder, Log_Names.files[i].file_name, &Log_Names.files[i].file_path, stk);
		STACK_ERROR_CHECK(status, stk);
	}

	return STACK_NO_ERROR;
}

StackStatusCode HtmlLogStarter(Stack_t* stk) {

	DIR* html_dir = opendir(Log_Names.folder);
	if (!html_dir)
		MakeHtmlFolder(stk);

	MakeHtmlFilePath(stk);

	FILE* log_file = fopen(Log_Names.files[MAIN].file_path, "w");
	if (!log_file)
		STACK_ERROR_CHECK(STACK_FILE_OPEN_ERROR, stk);

	fprintf(log_file, "<!DOCTYPE HTML PUBLIC>\n");
	fprintf(log_file, "<html>\n");

	fprintf(log_file, "\t<head>\n");
	fprintf(log_file, "\t\t<title>Stack Dump</title>\n");
	fprintf(log_file, "\t</head>\n");

	fprintf(log_file, "\t<style>\n");
	fprintf(log_file, "\t\t.anchor { \n\t\t\toutline: none; \n\t\t\ttext-decoration: none; \
			\n\t\t\tpadding: 2px 1px 0; \n\t\t}\n");
	fprintf(log_file, "\t\t.anchor:link { \n\t\t\tcolor: #fff; \n\t\t}\n");
	fprintf(log_file, "\t\t.anchor:visited { \n\t\t\tcolor: #fff; \n\t\t}\n");
	fprintf(log_file, "\t\t.anchor:focused { \n\t\t\tborder-bottom: 1px solid; \n\t\t\tbackground: #bae498; \n\t\t}\n");

	fprintf(log_file, "\t\t.table_header > td > h3{ \n\t\t\tpadding: 10px 20px; \n\t\t}\n");
	fprintf(log_file, "\t\t.stack_dump_number { \n\t\t\tcolor: turquoise; \n\t\t\ttext-align: center; \n\t\t}\n");
	fprintf(log_file, "\t\t.stack_pointer { \n\t\t\tcolor: red; \n\t\t\ttext-align: center; \n\t\t}\n");
	fprintf(log_file, "\t\t.stack_data_pointer { \n\t\t\tcolor: brown; \n\t\t\ttext-align: center; \n\t\t}\n");
	fprintf(log_file, "\t\t.stack_data { \n\t\t\tcolor: green; \n\t\t\ttext-align: left; \n\t\t}\n");
	fprintf(log_file, "\t\t.stack_capacity { \n\t\t\tcolor: blue; \n\t\t\ttext-align: center; \n\t\t}\n");
	fprintf(log_file, "\t\t.stack_size { \n\t\t\tcolor: violet; \n\t\t\ttext-align: center; \n\t\t}\n");

	fprintf(log_file, "\t\t.tb_stk { \n\t\t\twidth: 90%%; \n\t\t\tborder: 15px solid #F2F8F8; \
			\n\t\t\tborder-collapse: collapse; \n\t\t\tmargin: auto; \
			\n\t\t\ttable-layout: auto; \n\t\t\tmargin-bottom: 20px; \
			\n\t\t\tborder-top: 5px solid #F2F8F8; \n\t\t}\n");
	fprintf(log_file, "\t\t.tb_stk th { \n\t\t\tfont-weight: bold; \n\t\t\tpadding: 5px; \
			\n\t\t\tbackground: #F2F8F8; \n\t\t\tborder: none; \
			\n\t\t\tborder-bottom: 5px solid #F2F8F8; \n\t\t}\n");
	fprintf(log_file, "\t\t.tb_stk td { \n\t\t\tpadding: 10px; \n\t\t\tborder: none; \
			\n\t\t\tborder-bottom: 5px solid #F2F8F8; \n\t\t}\n");
	fprintf(log_file, "\t\t.table_header > td { \n\t\t\ttext-align: center; \n\t\t}\n");
	fprintf(log_file, "\t\t.tb_stk tbody tr:nth-child(odd) { \n\t\t\tbackground: #fff; \n\t\t}\n");
	fprintf(log_file, "\t\t.tb_stk tbody tr:nth-child(even) { \n\t\t\tbackground: #F7F7F7; \n\t\t}\n");

	fprintf(log_file, "\t\t.time { \n\t\t\tcolor: #4A235A; \n\t\t\tfont-size: 30px; \
			\n\t\t\tmargin: center; \n\t\t}\n");

	fprintf(log_file, "\t\t.btn { \n\t\t\tborder: none; \n\t\t\tborder-radius: 15px; \n\t\t\ttext-decoration: none; \
    		\n\t\t\tcolor: white; \n\t\t\tbackground: #0B63F6; \n\t\t\tbox-shadow: 0 5px 0 #003CC5; \
			\n\t\t\tfont-size: 16px; \n\t\t\tpadding-block: 8px; \n\t\t\tpadding-inline: 15px; \n\t\t}\n");
	fprintf(log_file, "\t\t.btn:hover { \n\t\t\tbackground: #003CC5; \n\t\t\tbox-shadow: none; \n\t\t\tposition: relative; \
    		\n\t\t\ttop: 5px; \n\t\t}\n");

	fprintf(log_file, "\t\th1[name='top'] { \n\t\t\tcolor: #4B0082; \n\t\t\tfont-style: italic; \
			\n\t\t\ttext-decoration: underline; \n\t\t}\n");
	fprintf(log_file, "\t</style>\n");

	fprintf(log_file, "\t<body>\n");
	fprintf(log_file, "\t\t<h1 align='center' name='top'><tt>MEGA DUMP</tt></h1>\n");
	fprintf(log_file, "\t\t<p><a href='#down' class='anchor'><button class='btn'><tt>Down</tt></button></a></p><br>\n");

	fprintf(log_file, "\t\t<table class='tb_stk'>\n");
	fprintf(log_file, "\t\t\t<tr class='table_header'>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Output number</tt></h3></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Stack pointer</tt></h3></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Stack data pointer</tt></h3></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Data</tt></h3></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Stack capacity</h3></tt></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Stack size</h3></tt></td>\n");
	fprintf(log_file, "\t\t\t</tr>\n");

	if (fclose(log_file))
		STACK_ERROR_CHECK(STACK_FILE_CLOSE_ERROR, stk);

	return STACK_NO_ERROR;
}

StackStatusCode StackDump(Stack_t* stk) {

	static size_t number = 1;

	FILE* log_file = fopen(Log_Names.files[MAIN].file_path, "a");
	if (!log_file)
		STACK_ERROR_CHECK(STACK_FILE_OPEN_ERROR, stk);

	fprintf(log_file, "\t\t\t<tr>\n");
	fprintf(log_file, "\t\t\t\t<td class = 'stack_dump_number'><tt>%zu</tt></td>\n", number++);
	fprintf(log_file, "\t\t\t\t<td class = 'stack_pointer'><tt>%p</tt></td>\n", stk);
	fprintf(log_file, "\t\t\t\t<td class = 'stack_data_pointer'><tt>%p</tt></td>\n", stk->data);

	fprintf(log_file, "\t\t\t\t<td class = 'stack_data'><tt>");
	for (size_t i = 0; i < stk->size; i++)
		fprintf(log_file, "%d ", *(stk->data + i));
	fprintf(log_file, "</tt></td>\n");

	fprintf(log_file, "\t\t\t\t<td class = 'stack_capacity'><tt>%zu</tt></td>\n", stk->capacity);
	fprintf(log_file, "\t\t\t\t<td class = 'stack_size'><tt>%zu</tt></td>\n", stk->size);
	fprintf(log_file, "\t\t\t</tr>\n");

	if (fclose(log_file))
		STACK_ERROR_CHECK(STACK_FILE_CLOSE_ERROR, stk);

	return STACK_NO_ERROR;
}

StackStatusCode HtmlLogFinisher(Stack_t* stk) {

	FILE* log_file = fopen(Log_Names.files[MAIN].file_path, "a");
	if (!log_file)
		STACK_ERROR_CHECK(STACK_FILE_OPEN_ERROR, stk);

	fprintf(log_file, "\t\t</table>\n");
	fprintf(log_file, "\t\t<p><a href='#top' name='down' class='anchor'><button class='btn'><tt>TOP</tt></button></a></p>\n");
	fprintf(log_file, "\t</body>\n");
	fprintf(log_file, "</html>\n");

	if (fclose(log_file))
		STACK_ERROR_CHECK(STACK_FILE_CLOSE_ERROR, stk);

	RunMainHtmlFile(stk);

	return STACK_NO_ERROR;
}

StackStatusCode RunMainHtmlFile(Stack_t* stk) {

	StackStatusCode status = STACK_NO_ERROR;

	char* open_log_file = NULL;
	status = StrConcatenation("open ", Log_Names.files[MAIN].file_path, &open_log_file, stk);
	STACK_ERROR_CHECK(status, stk);

	system(open_log_file);
	if (open_log_file)
		free(open_log_file);

	return STACK_NO_ERROR;
}

size_t StrLen(const char* str) {

	size_t length = 0;

	for (size_t i = 0; *(str + i) != '\0'; i++)
		length++;

	return length;
}

StackStatusCode StrConcatenation(const char* string1, const char* string2, char** str_out, Stack_t* stk) {

	size_t size = StrLen(string1) + StrLen(string2);

	*str_out = (char*)calloc(size + 1, sizeof(char));
	if (!str_out)
		STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);

	size_t i = 0;
	for (;*(string1 + i) != '\0'; i++)
		*(*str_out + i) = *(string1 + i);

	for (size_t j = 0; *(string2 + j) != '\0'; j++) {
		*(*str_out + i) = *(string2 + j);
		i++;
	}

	*(*str_out + i) = '\0';

	return STACK_NO_ERROR;
}

const char* StackErrorsMessenger(StackStatusCode status) {
	switch (status) {
		case STACK_NO_ERROR: 			return "STACK ERROR - NO";
		case STACK_ALLOC_ERROR: 		return "STACK ERROR - MEMORY ALLOCATION";
		case STACK_FILE_OPEN_ERROR:		return "STACK ERROR - FILE WAS NOT OPENED";
		case STACK_DIMENSIONS_ERROR:	return "STACK ERROR - WRONG DIMENSIONS OF STACK";
		case STACK_POINTER_ERROR:		return "STACK ERROR - STACK POINTER IS NULL";
		case STACK_DATA_POINTER_ERROR:	return "STACK ERROR - STACK DATA POINTER IS NULL";
		case STACK_FILE_CLOSE_ERROR:	return "STACK ERROR - FILE WAS NOT CLOSED";
		case STACK_UNDERFLOW:			return "STACK ERROR - 'ZERO' STACK";
		default:			 			return "UNDEFINED ERROR";
	}
}
