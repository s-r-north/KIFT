#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <stdarg.h>

typedef struct s_string
{
	char		*ptr;
	size_t		len;
}				t_string;

size_t	writefunc(void *ptr, size_t size, size_t nmemb, t_string *s)
{
	size_t newlen;
	newlen = s->len + size * nmemb;
	s->ptr = realloc(s->ptr, newlen + 1);
	memcpy(s->ptr + s->len, ptr, size * nmemb);
	s->ptr[newlen] = '\0';
	s->len = newlen;

	return (size * nmemb);
}

void	curl(int opts, char *url, char *h2)
{
	t_string s;
	struct curl_slist *list = NULL;
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	s.len = 0;
	s.ptr = malloc(1);
	if(curl) {
    	curl_easy_setopt(curl, CURLOPT_URL, url);
    	list = curl_slist_append(curl, h2);
    	list = list->next;
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
    	res = curl_easy_perform(curl);
    	curl_easy_cleanup(curl);
  	}
  	
}

char	*sentence_to_query(char *sentence)
{
	size_t i;
	size_t quotecount;
	char *query;

	i = -1;
	quotecount = 0;
	while (sentence[++i])
	{
		if (sentence[i] == ' ')
			sentence[i] = '+';
		if (sentence[i] == '\"' || sentence[i] == '\'')
			quotecount++;
	}
	if (!quotecount)
		return(sentence);
}

int	main(int ac, char **av)
{
	// char *h1;
	char *h2;
	char *url;

	asprintf(&url, "https://api.spotify.com/v1/search?q=%s&type=track", sentence_to_query(av[2]));
	// h1 = "Accept: application/json";
	asprintf(&h2, "Authorization: Bearer %s", av[1]);
	curl(1, url, h2);
	return (0);
}

// curl -X PUT "https://api.spotify.com/v1/me/player/play" -H "Accept: application/json" -H "Authorization: Bearer BQDHIRskTd7XdTSctdUhdEZNmk039T2ba2ssjSKmup-MVzEJk5c_4XY4Z5qISgkuI3KXUVV7Q3Dev0lgTWZHNq3DnISE-ONvOiGQn7x6O3_b4dE0tb7UciMY9MijfagYnKYy-hoGErh9icAPUfundQ" -H "Content-Type: application/json" --data "{\"context_uri\":\"%s\"}"