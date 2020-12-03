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

        jNews->source = jNews->source.substr(1, jNews->source.size() - 3); //remove quotes from source

    }
   catch (std::exception& e)
    {
        std::cout << e.what() << "n";
    }


}

void NewsModule::initializeNews(std::string searchString)
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

      ///connect to site and receive transfer, after transfer is received callback function is called
      code = curl_easy_perform(curlHandler);

      ///Check for errors
      if(code != CURLE_OK)
      {
          std::cout << "curl_easy_perform() failed\n";
          std::cout << curl_easy_strerror(code);
      }

      saveJson(&newsToDisplay, news);

    }
    curl_easy_cleanup(curlHandler);
}
void NewsModule::populateModule()
{

    std::cout << "Start populating custom Module" << std::endl;

    this->box = Gtk::VBox();
    this->frame.remove();
    this->frame.add(this->box);

    /// Create a labels for the module
    this->sourceLabel = Gtk::Label();
    sourceLabel.set_markup("<b><u>" + newsToDisplay.source + "</u></b>");
    sourceLabel.set_justify(Gtk::JUSTIFY_LEFT);
    this->box.pack_start(this->sourceLabel, Gtk::PACK_SHRINK, 0);

    this->titleLabel = Gtk::Label();
    titleLabel.set_max_width_chars(40);
    titleLabel.set_line_wrap(true);
    titleLabel.set_markup(newsToDisplay.title);
    titleLabel.set_justify(Gtk::JUSTIFY_LEFT);
    this->box.pack_start(this->titleLabel, Gtk::PACK_SHRINK, 0);

    this->dateLabel = Gtk::Label();
    dateLabel.set_max_width_chars(40);
    dateLabel.set_line_wrap(true);
    dateLabel.set_text("Date: " + newsToDisplay.date);
    dateLabel.set_justify(Gtk::JUSTIFY_LEFT);
    this->box.pack_start(this->dateLabel, Gtk::PACK_SHRINK, 0);

    this->descLabel = Gtk::Label();
    descLabel.set_max_width_chars(40);
    descLabel.set_line_wrap(true);
    descLabel.set_markup(newsToDisplay.description);
    descLabel.set_justify(Gtk::JUSTIFY_LEFT);
    this->box.pack_start(this->descLabel, Gtk::PACK_SHRINK, 0);

    this->box.set_orientation(Gtk::ORIENTATION_VERTICAL);
    this->box.set_size_request(530,400);

    std::thread newsThread(&NewsModule::refresher, this, this->searchString);
    newsThread.detach();

    std::cout << "Finished populating news module" << std::endl;


  }

void NewsModule::refresher(std::string searchString){
    while(true){
        std::this_thread::sleep_for (std::chrono::seconds(20));
        NewsModule::refreshArticles(searchString);
    }
}

void NewsModule::refreshArticles(std::string searchString){
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

      ///connect to site and receive transfer, after transfer is received callback function is called
      code = curl_easy_perform(curlHandler);

      ///Check for errors
      if(code != CURLE_OK)
      {
          std::cout << "curl_easy_perform() failed\n";
          std::cout << curl_easy_strerror(code);
      }

      saveJson(&newsToDisplay, news);

    }
    curl_easy_cleanup(curlHandler);

}
