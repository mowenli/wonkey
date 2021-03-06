
#ifndef WX_LITEHTML_GLUE_H
#define WX_LITEHTML_GLUE_H

#include <wxwonkey.h>
#include <litehtml.h>

class wx_litehtml_document_container : public wxObject,public litehtml::document_container{

	protected:

	virtual wxObject*	_create_font( wxString faceName,wxInt size,wxInt weight,litehtml::font_style style,wxUInt decoration,litehtml::font_metrics *fm )=0;

	virtual void		_delete_font( wxObject *font )=0;

	virtual wxInt		_text_width( wxString text,wxObject *font )=0;

	virtual void		_draw_text( wxObject *hdc,wxString text,wxObject *font,litehtml::web_color *color,litehtml::position *pos )=0;
	
	virtual wxInt		_pt_to_px( int pt )=0;
	
	virtual wxInt		_get_default_font_size()=0;
	
	virtual wxString	_get_default_font_name()=0;
	
	virtual void		_draw_list_marker( wxObject *hdc,litehtml::list_marker *marker )=0;
	
	virtual void		_load_image( wxString src,wxString baseurl,wxBool redraw_on_ready )=0;
	
	virtual void		_get_image_size( wxString src,wxString baseurl,litehtml::size *sz )=0;
	
	virtual void		_draw_background( wxObject *hdc,wxString img_src,wxString img_baseurl,litehtml::background_paint *bg )=0;

	virtual void		_draw_borders( wxObject *hdc,litehtml::borders *borders,litehtml::position *draw_pos,wxBool root )=0;
	
	virtual void		_set_caption( wxString caption )=0;
	
	virtual void		_set_base_url( wxString base_url )=0;

	virtual void		_on_anchor_click( wxString url )=0;
	
	virtual void		_set_cursor( wxString cursor )=0;
	
	virtual wxString	_import_css( wxString url,wxString baseurl )=0;
	
	virtual void		_set_clip( litehtml::position *pos,litehtml::border_radiuses *bdr_radius )=0;
	
	virtual void		_del_clip()=0;
	
	virtual void		_get_client_rect( litehtml::position *client )=0;
	
	virtual void		_get_media_features( litehtml::media_features *media )=0;
	
	virtual wxString	_get_language()=0;
	
	virtual wxString	_get_culture()=0;

	//**** *document_container ******

	litehtml::uint_ptr	create_font( const litehtml::tchar_t *faceName,int size,int weight,litehtml::font_style italic,unsigned int decoration,litehtml::font_metrics *fm );
	
	void				delete_font( litehtml::uint_ptr hFont );
	
	int					text_width( const litehtml::tchar_t *text,litehtml::uint_ptr hFont );
	
	void				draw_text( litehtml::uint_ptr hdc,const litehtml::tchar_t *text,litehtml::uint_ptr hFont,litehtml::web_color color,const litehtml::position &pos );
	
	int					pt_to_px( int pt );
	
	int					get_default_font_size()const;
	
	const litehtml::tchar_t *get_default_font_name()const;	
	
	void				draw_list_marker( litehtml::uint_ptr hdc,const litehtml::list_marker &marker );
	
	void				load_image( const litehtml::tchar_t *src,const litehtml::tchar_t *baseurl,bool redraw_on_ready );
	
	void				get_image_size( const litehtml::tchar_t *src,const litehtml::tchar_t *baseurl,litehtml::size &sz );
	
	void				draw_background( litehtml::uint_ptr hdc,const litehtml::background_paint &bg );
	
	void				draw_borders( litehtml::uint_ptr hdc,const litehtml::borders &borders,const litehtml::position &draw_pos,bool root );
	
	void				set_caption( const litehtml::tchar_t *caption );
	
	void				set_base_url( const litehtml::tchar_t *base_url );
	
	void				link( const std::shared_ptr<litehtml::document> &doc,const litehtml::element::ptr &el );
	
	void				on_anchor_click( const litehtml::tchar_t *url,const litehtml::element::ptr &el );
	
	void				set_cursor( const litehtml::tchar_t *cursor );
	
	void				transform_text( litehtml::tstring &text,litehtml::text_transform tt );
	
	void				import_css( litehtml::tstring &text,const litehtml::tstring &url,litehtml::tstring &baseurl );
	
	void				set_clip( const litehtml::position &pos,const litehtml::border_radiuses &bdr_radius,bool valid_x,bool valid_y );
	
	void				del_clip();
	
	void				get_client_rect( litehtml::position &client )const;
	
	std::shared_ptr<litehtml::element>	create_element( const litehtml::tchar_t *tag_name,
																 const litehtml::string_map &attributes,
																 const std::shared_ptr<litehtml::document> &doc );
	
	void				get_media_features( litehtml::media_features &media )const;
	
	void				get_language( litehtml::tstring &language,litehtml::tstring  &culture )const;
};

class wx_litehtml_context : public wxObject,public litehtml::context{

	public:

	wx_litehtml_context();
	
	void				load_master_stylesheet( wxString master_css );
	
};

class wx_litehtml_document : public wxObject{

	public:
	
	wx_litehtml_document( wxString source,wx_litehtml_document_container *container,wx_litehtml_context *context );
	
	~wx_litehtml_document();
	
	void				render( int max_width );
	
	void				draw( wxObject *hdc,int x,int y,litehtml::position *clip );
	
	int					width();
	
	int					height();
	
	void				media_changed();
	
	void				on_mouse_over( int x,int y,int client_x,int client_y ); 
	
	void				on_lbutton_down( int x,int y,int client_x,int client_y ); 

	void				on_lbutton_up( int x,int y,int client_x,int client_y ); 

	void				on_mouse_leave();

	private:
	
	litehtml::document::ptr _document{};
	
	wx_litehtml_document_container *_container{};
	wx_litehtml_context *_context{};
	wxObject *_drawing{};
	
	void gcMark();
};

#endif
 