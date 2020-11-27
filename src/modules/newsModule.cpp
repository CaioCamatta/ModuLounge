#include "newsModule.h"

size_t NewsModule::saveData(void *contents, size_t size, size_t nmemb, void *userp)
{

    size_t trueSize = size * nmemb;
    struct newsData *news = (struct newsData*)userp;

    char *ptr = (char*)realloc(news->data, news->size + trueSize + 1);
    if(ptr == NULL)
    {
        std::cout << "Not enough memory available\n";
        return 0;
    }

    news->data = ptr;
    memcpy(&(news->data[news->size]), contents, trueSize);
    news->size = news->size + trueSize;
    //end array with 0
    news->data[news->size] = 0;

    return trueSize;
    return 0;
}

/*Save all the important data from json format to
* the jsonNews struct for later use
*/
void NewsModule::saveJson(jsonNews *jNews, newsData news)
{
    Json::Reader jsonRead;
    Json::Value root;
    Json::Value articles;
    jsonRead.parse(news.data, root);
    articles = root.get("articles", "No articles available");
   try
    {
        jNews->description = articles[1].get("description", "No Description").toStyledString();
        jNews->date = articles[1].get("publishedAt", "No Date").toStyledString();
        Json::Value fullSource = articles[1].get("source", "No source available");
        jNews->source = fullSource.get("name", "No Name").toStyledString();
        jNews->title = articles[1].get("title", "No Title").toStyledString();
        jNews->content = articles[1].get("content", "No Content").toStyledString();

    }
   catch (std::exception& e)
    {
        std::cout << e.what() << "n";
    }


}

void NewsModule::populateModule()
{
  CURL *curlHandler;
  CURLcode code;
  struct newsData news;
  news.data = (char*)malloc(1); //temporary malloc
  news.size = 0;

  std::string newsString;

  curlHandler = curl_easy_init();
  if(curlHandler)
  {
    curl_easy_setopt(curlHandler, CURLOPT_URL, searchString.c_str());

    curl_easy_setopt(curlHandler, CURLOPT_WRITEFUNCTION, saveData);

    curl_easy_setopt(curlHandler, CURLOPT_WRITEDATA, (void *)&news);

    /*connect to site and receive transfer, after transfer is received callback function is called */
    code = curl_easy_perform(curlHandler);

    /* Check for errors */
    if(code != CURLE_OK)
    {
        std::cout << "curl_easy_perform() failed\n";
        std::cout << curl_easy_strerror(code);
    }
    //struct jsonNews newsToDisplay;
    saveJson(&newsToDisplay, news);
    std::cout << "Start populating custom Module" << std::endl;

    // Create a button, with label of the source of news
    this->button = Gtk::Button(newsToDisplay.source);

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    this->button.signal_clicked().connect(sigc::mem_fun(*this,
                                                        &NewsModule::on_button_clicked));

    // Add Button to our Box (the Box holds all the widgets of this Module)
    // Shrink Widget to its size, add 0 padding
    this->box.pack_start(button, Gtk::PACK_SHRINK,0);

    std::cout << "Finished populating custom Module" << std::endl;


  }

  curl_easy_cleanup(curlHandler);

}
void NewsModule::on_button_clicked()
{
    std::cout << "News From " << newsToDisplay.source << std::endl;
    std::cout << "Title: " << newsToDisplay.title << std::endl;
    std::cout << "Date: " << newsToDisplay.date << std::endl;
    std::cout << "Description: " << newsToDisplay.description << std::endl;
    std::cout << "Content: " << newsToDisplay.content << std::endl;
}
