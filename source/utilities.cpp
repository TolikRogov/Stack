#include "../include/utilities.hpp"

StackStatusCode HtmlLogStarter(Stack_t* stk) {

	FILE* log_file = fopen(LOG_FILE_PATH, "w");
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
	fprintf(log_file, "\t\t.stack_pointer { \n\t\t\tcolor: red; \n\t\t}\n");
	fprintf(log_file, "\t\t.stack_data_pointer { \n\t\t\tcolor: brown; \n\t\t}\n");
	fprintf(log_file, "\t\t.stack_data { \n\t\t\tcolor: green; \n\t\t\ttext-align: left; \n\t\t}\n");
	fprintf(log_file, "\t\t.stack_capacity { \n\t\t\tcolor: blue; \n\t\t}\n");
	fprintf(log_file, "\t\t.stack_size { \n\t\t\tcolor: violet; \n\t\t}\n");

	fprintf(log_file, "\t\t.tb_stk { \n\t\t\twidth: 80%%; \n\t\t\tborder: 15px solid #F2F8F8; \
			\n\t\t\tborder-collapse: collapse; \n\t\t\tmargin: auto; \
			\n\t\t\ttable-layout: auto; \n\t\t\tmargin-bottom: 20px; \
			\n\t\t\tborder-top: 5px solid #F2F8F8; \n\t\t}\n");
	fprintf(log_file, "\t\t.tb_stk th { \n\t\t\tfont-weight: bold; \n\t\t\tpadding: 5px; \
			\n\t\t\tbackground: #F2F8F8; \n\t\t\tborder: none; \
			\n\t\t\tborder-bottom: 5px solid #F2F8F8; \n\t\t}\n");
	fprintf(log_file, "\t\t.tb_stk td { \n\t\t\tpadding: 10px; \n\t\t\tborder: none; \
			\n\t\t\ttext-align: center; \n\t\t\tborder-bottom: 5px solid #F2F8F8; \n\t\t}\n");
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
	fprintf(log_file, "\t\t<p><a href='#time' class='anchor'><button class='btn'><tt>Working time of program</tt></button></a></p><br>\n");

	fclose(log_file);

	return STACK_NO_ERROR;
}

StackStatusCode StackDump(Stack_t* stk) {

	static size_t number = 1;

	FILE* log_file = fopen(LOG_FILE_PATH, "a");
	if (!log_file)
		STACK_ERROR_CHECK(STACK_FILE_OPEN_ERROR, stk);

	fprintf(log_file, "\t\t<h2 align = 'center'>DUMP #%zu</h2>\n", number++);
	fprintf(log_file, "\t\t<table class='tb_stk'>\n");

	fprintf(log_file, "\t\t\t<tr class='table_header'>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Stack pointer</tt></h3></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Stack data pointer</tt></h3></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Data</tt></h3></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Stack capacity</h3></tt></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Stack size</h3></tt></td>\n");
	fprintf(log_file, "\t\t\t</tr>\n");

	fprintf(log_file, "\t\t\t<tr>\n");
	fprintf(log_file, "\t\t\t\t<td class = 'stack_pointer'><tt>%p</tt></td>\n", stk);
	fprintf(log_file, "\t\t\t\t<td class = 'stack_data_pointer'><tt>%p</tt></td>\n", stk->data);
	fprintf(log_file, "\t\t\t\t<td class = 'stack_data'><tt>%d</tt></td>\n", *(stk->data + stk->size - 1));
	fprintf(log_file, "\t\t\t\t<td class = 'stack_capacity'><tt>%zu</tt></td>\n", stk->capacity);
	fprintf(log_file, "\t\t\t\t<td class = 'stack_size'><tt>%zu</tt></td>\n", stk->size);
	fprintf(log_file, "\t\t\t</tr>\n");

	fprintf(log_file, "\t\t</table>\n");

	fclose(log_file);

	return STACK_NO_ERROR;
}

StackStatusCode HtmlLogFinisher(Stack_t* stk) {

	FILE* log_file = fopen(LOG_FILE_PATH, "a");
	if (!log_file)
		STACK_ERROR_CHECK(STACK_FILE_OPEN_ERROR, stk);

	fprintf(log_file, "\t\t<p><a href='#top' class='anchor'><button class='btn'><tt>TOP</tt></button></a></p>\n");
	fprintf(log_file, "\t</body>\n");
	fprintf(log_file, "</html>\n");

	fclose(log_file);

	system("open log_eblan.html");

	return STACK_NO_ERROR;
}

const char* ErrorsMessenger(StackStatusCode status) {
	switch (status) {
		case STACK_NO_ERROR: 		return "STACK NO ERROR";
		case STACK_ALLOC_ERROR: 	return "STACK MEMORY ALLOCATION ERROR";
		case STACK_FILE_OPEN_ERROR:	return "STACK FILE OPEN ERROR";
		default:			 		return "UNDEFINED ERROR";
	}
}
