#include "../include/utilities.hpp"

StackStatusCode HtmlMainLogStarter(Stack_t* stk) {

	StackStatusCode status = STACK_NO_ERROR;

	status = MakeLpFolders(stk);
	STACK_ERROR_CHECK(status, stk);

	status = MakeFilesPath(stk);
	STACK_ERROR_CHECK(status, stk);

	FILE* main_file = fopen(stk->log_parts[HTML].files[MAIN].file_path, "w");
	if (!main_file)
		STACK_ERROR_CHECK(STACK_FILE_OPEN_ERROR, stk);

	fprintf(main_file, "<!DOCTYPE HTML PUBLIC>\n");
	fprintf(main_file, "<html>\n");

	fprintf(main_file, "\t<head>\n");
	fprintf(main_file, "\t\t<title>Stack Dump</title>\n");

	fprintf(main_file, "\t\t<link rel='stylesheet' href='%s'>\n", stk->log_parts[STYLE].files[CSS].file_path);

	fprintf(main_file, "\t</head>\n");

	status = CssLogStarter(stk);
	STACK_ERROR_CHECK(status, stk);

	fprintf(main_file, "\t<body>\n");
	fprintf(main_file, "\t\t<h1 align='center' name='top'><tt>MEGA DUMP</tt></h1>\n");
	fprintf(main_file, "\t\t<p><a href='#down' class='anchor'><button class='btn'><tt>Down</tt></button></a></p><br>\n");

#ifdef HTML_DUMP
	fprintf(main_file, "\t\t<p class = 'stack_info'><tt>Stack_t[%p] born at %s:%zu, name '%s'</tt></p>\n",
			stk, stk->file_name, stk->line, stk->stack_name);
#endif

	// fprintf(main_file, "\t\t<table class='tb_stk'>\n");
	// fprintf(main_file, "\t\t\t<tr class='table_header'>\n");
	// fprintf(main_file, "\t\t\t\t<td><tt><h3>Output number</tt></h3></td>\n");
	// fprintf(main_file, "\t\t\t\t<td><tt><h3>Stack pointer</tt></h3></td>\n");
	// fprintf(main_file, "\t\t\t\t<td><tt><h3>Stack data pointer</tt></h3></td>\n");
	// fprintf(main_file, "\t\t\t\t<td><tt><h3>Data</tt></h3></td>\n");
	// fprintf(main_file, "\t\t\t\t<td><tt><h3>Stack capacity</h3></tt></td>\n");
	// fprintf(main_file, "\t\t\t\t<td><tt><h3>Stack size</h3></tt></td>\n");
	// fprintf(main_file, "\t\t\t</tr>\n");

	if (fclose(main_file))
		STACK_ERROR_CHECK(STACK_FILE_CLOSE_ERROR, stk);

	return STACK_NO_ERROR;
}

StackStatusCode CssLogStarter(Stack_t* stk) {

	FILE* styles_file = fopen(stk->log_parts[STYLE].files[CSS].file_path, "w");
	if (!styles_file)
		STACK_ERROR_CHECK(STACK_FILE_OPEN_ERROR, stk);

	fprintf(styles_file, ".anchor { \n\toutline: none; \n\ttext-decoration: none; \
			\n\tpadding: 2px 1px 0; \n}\n");
	fprintf(styles_file, ".anchor:link { \n\tcolor: #fff; \n}\n\n");
	fprintf(styles_file, ".anchor:visited { \n\tcolor: #fff; \n}\n\n");
	fprintf(styles_file, ".anchor:focused { \n\tborder-bottom: 1px solid; \n\tbackground: #bae498; \n}\n\n");

	fprintf(styles_file, ".table_header > td > h3{ \n\tpadding: 10px 20px; \n}\n\n");
	fprintf(styles_file, ".stack_dump_number { \n\tcolor: turquoise; \n\ttext-align: center; \n}\n\n");
	fprintf(styles_file, ".stack_pointer { \n\tcolor: red; \n\ttext-align: center; \n}\n\n");
	fprintf(styles_file, ".stack_data_pointer { \n\tcolor: brown; \n\ttext-align: center; \n}\n\n");
	fprintf(styles_file, ".stack_data { \n\tcolor: green; \n\ttext-align: left; \n}\n\n");
	fprintf(styles_file, ".stack_capacity { \n\tcolor: blue; \n\ttext-align: center; \n}\n\n");
	fprintf(styles_file, ".stack_size { \n\tcolor: violet; \n\ttext-align: center; \n}\n\n");

	fprintf(styles_file, ".tb_stk { \n\twidth: 90%%; \n\tborder: 15px solid #F2F8F8; \
			\n\tborder-collapse: collapse; \n\tmargin: auto; \
			\n\ttable-layout: auto; \n\tmargin-bottom: 20px; \
			\n\tborder-top: 5px solid #F2F8F8; \n}\n\n");
	fprintf(styles_file, ".tb_stk th { \n\tfont-weight: bold; \n\tpadding: 5px; \
			\n\tbackground: #F2F8F8; \n\tborder: none; \
			\n\tborder-bottom: 5px solid #F2F8F8; \n}\n\n");
	fprintf(styles_file, ".tb_stk td { \n\tpadding: 10px; \n\tborder: none; \
			\n\tborder-bottom: 5px solid #F2F8F8; \n}\n\n");
	fprintf(styles_file, ".table_header > td { \n\ttext-align: center; \n\t\t}\n\n");
	fprintf(styles_file, ".tb_stk tbody tr:nth-child(odd) { \n\tbackground: #fff; \n\t\t}\n\n");
	fprintf(styles_file, ".tb_stk tbody tr:nth-child(even) { \n\tbackground: #F7F7F7; \n}\n\n");

	fprintf(styles_file, ".time { \n\tcolor: #4A235A; \n\tfont-size: 30px; \
			\n\tmargin: center; \n}\n\n");

	fprintf(styles_file, ".btn { \n\tborder: none; \n\tborder-radius: 15px; \n\ttext-decoration: none; \
    		\n\tcolor: white; \n\tbackground: #0B63F6; \n\tbox-shadow: 0 5px 0 #003CC5; \
			\n\tfont-size: 16px; \n\tpadding-block: 8px; \n\tpadding-inline: 15px; \n}\n\n");
	fprintf(styles_file, ".btn:hover { \n\tbackground: #003CC5; \n\tbox-shadow: none; \n\tposition: relative; \
    		\n\ttop: 5px; \n}\n\n");

	fprintf(styles_file, "h1[name='top'] { \n\tcolor: #4B0082; \n\tfont-style: italic; \
			\n\ttext-decoration: underline; \n}\n\n");

	if (fclose(styles_file))
		STACK_ERROR_CHECK(STACK_FILE_CLOSE_ERROR, stk);

	return STACK_NO_ERROR;
}

StackStatusCode HtmlMainLogFinisher(Stack_t* stk) {

	FILE* main_file = fopen(stk->log_parts[HTML].files[MAIN].file_path, "a");
	if (!main_file)
		STACK_ERROR_CHECK(STACK_FILE_OPEN_ERROR, stk);

	//fprintf(main_file, "\t\t</table>\n");
	fprintf(main_file, "\t\t<p><a href='#top' name='down' class='anchor'><button class='btn'><tt>TOP</tt></button></a></p>\n");
	fprintf(main_file, "\t</body>\n");
	fprintf(main_file, "</html>\n");

	if (fclose(main_file))
		STACK_ERROR_CHECK(STACK_FILE_CLOSE_ERROR, stk);

	RunMainHtmlFile(stk);

	return STACK_NO_ERROR;
}

StackStatusCode MakeLpFolders(Stack_t* stk) {

	StackStatusCode status = STACK_NO_ERROR;

	for (size_t i = 0; i < LP_END; i++) {
		DIR* cur_dir = opendir(stk->log_parts[i].folder);
		if (cur_dir) {
			closedir(cur_dir);
			continue;
		}

		char* make_folder = NULL;
		status = StrConcatenation("mkdir ", stk->log_parts[i].folder, &make_folder, stk);
		STACK_ERROR_CHECK(status, stk);

		system(make_folder);
		if (make_folder)
			free(make_folder);
	}

	return STACK_NO_ERROR;
}

StackStatusCode MakeFilesPath(Stack_t* stk) {

	StackStatusCode status = STACK_NO_ERROR;

	for (size_t i = 0; i < LP_END; i++) {

		for (size_t j = 0; j < stk->log_parts[i].files_size; j++) {
			status = StrConcatenation(stk->log_parts[i].folder, stk->log_parts[i].files[j].file_name,
									&stk->log_parts[i].files[j].file_path, stk);
			STACK_ERROR_CHECK(status, stk);
		}
	}

	return STACK_NO_ERROR;
}

StackStatusCode DoStackDump(Stack_t* stk) {

	//static size_t number = 1;

	FILE* main_file = fopen(stk->log_parts[HTML].files[MAIN].file_path, "a");
	if (!main_file)
		STACK_ERROR_CHECK(STACK_FILE_OPEN_ERROR, stk);

	FILE* table_file = fopen(stk->log_parts[HTML].files[TABLE].file_path, "a");
	if (!table_file)
		STACK_ERROR_CHECK(STACK_FILE_OPEN_ERROR, stk);

// 	fprintf(log_file, "\t\t\t<tr>\n");
// 	fprintf(log_file, "\t\t\t\t<td class = 'stack_dump_number'><tt>%zu</tt></td>\n", number++);
// 	fprintf(log_file, "\t\t\t\t<td class = 'stack_pointer'><tt>%p</tt></td>\n", stk);
// 	fprintf(log_file, "\t\t\t\t<td class = 'stack_data_pointer'><tt>%p</tt></td>\n", stk->data);
//
// 	fprintf(log_file, "\t\t\t\t<td class = 'stack_data'><tt>");
// 	for (size_t i = 0; i < stk->size; i++)
// 		fprintf(log_file, "%d ", *(stk->data + i));
// 	fprintf(log_file, "</tt></td>\n");
//
// 	fprintf(log_file, "\t\t\t\t<td class = 'stack_capacity'><tt>%zu</tt></td>\n", stk->capacity);
// 	fprintf(log_file, "\t\t\t\t<td class = 'stack_size'><tt>%zu</tt></td>\n", stk->size);
// 	fprintf(log_file, "\t\t\t</tr>\n");

	if (fclose(main_file))
		STACK_ERROR_CHECK(STACK_FILE_CLOSE_ERROR, stk);

	if (fclose(table_file))
		STACK_ERROR_CHECK(STACK_FILE_CLOSE_ERROR, stk);

	return STACK_NO_ERROR;
}

StackStatusCode RunMainHtmlFile(Stack_t* stk) {

	StackStatusCode status = STACK_NO_ERROR;

	char* open_log_file = NULL;
	status = StrConcatenation("open ", stk->log_parts[HTML].files[MAIN].file_path, &open_log_file, stk);
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
		case STACK_EMPTY_ERROR:			return "STACK ERROR - STACK IS EMPTY";
		default:			 			return "UNDEFINED ERROR";
	}
}
