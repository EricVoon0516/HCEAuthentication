# LAYOUT
> Documentation: https://developer.android.com/develop/ui/views/layout/declaring-layout
>
> This is the section to be designed for layer presentation of every activities. Fo example, you may insert button and other elements in this section for user to interact with the particular layer of application's task.
> XML (Extensible Markup Language) is used in this section.
>
> For example: `activity_main.xml`
>
> ```
> <?xml version="1.0" encoding="utf-8"?>
> <androidx.constraintlayout.widget.ConstraintLayout xmlns:android="http://schemas.android.com/apk/res/android"
>     xmlns:app="http://schemas.android.com/apk/res-auto"
>     xmlns:tools="http://schemas.android.com/tools"
>     android:id="@+id/hce"
>     android:layout_width="match_parent"
>     android:layout_height="match_parent">
> 
>     <Button
>         android:id="@+id/hce_button"
>         android:layout_width="wrap_content"
>         android:layout_height="wrap_content"
>         android:text="Button"
>         app:layout_constraintBottom_toBottomOf="parent"
>         app:layout_constraintEnd_toEndOf="parent"
>         app:layout_constraintStart_toStartOf="parent"
>         app:layout_constraintTop_toTopOf="parent" />
> </androidx.constraintlayout.widget.ConstraintLayout>
> ```
> ![image](https://github.com/EricVoon0516/HCEAuthentication/assets/96558437/e49648b3-d078-47c6-972c-ee3e6c4be4dc)
> 
